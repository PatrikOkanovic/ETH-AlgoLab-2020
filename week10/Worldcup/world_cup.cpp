#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> SolT;

long floor_to_double(const SolT &x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

void test_case() {
  int n, m, c;
  std::cin >> n >> m >> c;

  std::vector<K::Point_2> s_w(n+m);
  std::vector<IT> warehouses(n);

  Program lp(CGAL::SMALLER, true, 0, false, 0);
  for(int i = 0; i < n; ++i) {
    IT s;
    std::cin >> s_w[i] >> s >> warehouses[i];
    lp.set_b(i, s);
  }

  for(int i = 0; i < m; ++i) {
    IT d, u;
    std::cin >> s_w[i+n] >> d >> u;
    u *= 100;
    lp.set_b(n + i, d);
    lp.set_b(n + m + i, -d);
    lp.set_b(n + 2*m + i, u);
  }

  int counter = 0;
  std::vector<std::vector<std::pair<int, double>>> revenues(n, std::vector<std::pair<int, double>>(m));
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      counter++;
      double revenue; std::cin >> revenue;
      revenues[i][j] = std::make_pair(counter, -revenue);
      
      lp.set_a(counter, i, 1);
      lp.set_a(counter, n + j, 1);
      lp.set_a(counter, n + m + j, -1);
      lp.set_a(counter, n + 2*m + j, warehouses[i]);
    }
  }

  Triangulation tri;
  tri.insert(s_w.begin(), s_w.end());
  for(int i = 0; i < c; ++i) {
    K::Point_2 contour;
    long r;
    std::cin >> contour >> r;
    long r2 = r*r;
    if(CGAL::squared_distance(tri.nearest_vertex(contour)->point(), contour) <= r2) {
      for(int i = 0; i < n; ++i) {
        bool sign1 = CGAL::squared_distance(contour, s_w[i]) <= r2;
        for(int j = 0; j < m; ++j) {
          bool sign2 = CGAL::squared_distance(contour, s_w[n+j]) <= r2;
          if(sign1 != sign2) {
            revenues[i][j].second += 0.01;
          }
        }
      }
    }    
  }

  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      lp.set_c(revenues[i][j].first, revenues[i][j].second);
    }
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  

  if(s.is_infeasible()) std::cout << "RIOT!\n";
  else std::cout << floor_to_double(-s.objective_value()) << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;

  for(int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
