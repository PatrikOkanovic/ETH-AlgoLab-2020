#include <iostream>
#include <vector>
#include <utility>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


void test_case() {
  int z, u, v, w;
  std::cin >> z >> u >> v >> w;
  int a, g;
  std::cin >> a >> g;
  
  std::vector<int> where(g), who(g), how(g);
  std::vector< std::pair<K::Point_2,int> > pts;

  for (int i = 0; i < g; ++i) {
    int x, y;
    std::cin >> x >> y >> where[i] >> who[i] >> how[i]; 
    pts.push_back(std::make_pair(K::Point_2(x,y), i));
  }
  
  Triangulation t; 
  t.insert(pts.begin(), pts.end());
  
  std::vector<int> cost(g, std::numeric_limits<int>::max());
  for (int i = 0; i < a; ++i) {
    int x, y, z_i;
    std::cin >> x >> y >> z_i; 

    int near_gang = t.nearest_vertex(K::Point_2(x, y))->info();
    cost[near_gang] = std::min(z_i, cost[near_gang]);
  }
  

  Program lp (CGAL::LARGER, true, 0, true, 24);
  lp.set_b(0, u);
  lp.set_b(1, v);
  lp.set_b(2, w);
  int h = 0;
  for(int i = 0; i < g; ++i){
    if(cost[i] == std::numeric_limits<int>::max()) continue;
    
    lp.set_a(h, 0, where[i]);
    lp.set_a(h, 1, who[i]);
    lp.set_a(h, 2, how[i]);
    lp.set_c(h, cost[i]);

    h++;
  }
  
  Solution s = CGAL::solve_linear_program(lp, ET()); 

  if (!s.is_optimal() || s.objective_value() > z) std::cout << "H\n";
  else std::cout << "L\n";
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;

  for(int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
