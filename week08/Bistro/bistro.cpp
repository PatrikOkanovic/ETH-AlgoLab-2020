#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_faces_iterator  Face_iterator;

long floor_to_long(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void test_case(int n) {
  
  std::vector<K::Point_2> pts;
  pts.reserve(n);
  for(int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }
  
  // construct triangulation
  Triangulation t;
  t.insert(pts.begin(), pts.end());
  
  int m; std::cin >> m;
  for(int i = 0; i < m; ++i) {
    int x, y;
    std::cin >> x >> y;
    K::Point_2 p (x, y);
    auto v = t.nearest_vertex(K::Point_2(x, y));
    std::cout << floor_to_long(CGAL::squared_distance(v->point(), p)) << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  
  while(true) {
    int n; std::cin >> n;
    if(n == 0) break;
    test_case(n);
   }
  
  return 0;
}
