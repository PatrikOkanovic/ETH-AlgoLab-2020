#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef Triangulation::Finite_edges_iterator Edge_iterator;


void test_case(int n) {
  int l, b, r, t;
  std::cin >> l >> b >> r >> t;
  
  std::vector<K::Point_2> pts;
  pts.reserve(n);
  for(int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }
  
  // construct triangulation
  Triangulation triangulation;
  triangulation.insert(pts.begin(), pts.end());
  
  std::unordered_map<K::Point_2, double> distances;
  
  for(Vertex_iterator v = triangulation.finite_vertices_begin(); v != triangulation.finite_vertices_end(); ++v) {
    K::Point_2 point = v->point();
    distances[point] = std::min(std::min(point.x() - l, r - point.x()), std::min(point.y() - b, t - point.y()));
  }
  
  for(Edge_iterator e = triangulation.finite_edges_begin(); e != triangulation.finite_edges_end(); ++e) {
    K::Segment_2 segment = triangulation.segment(e);
    K::Point_2 source = segment.source();
    K::Point_2 target = segment.target();
    double dx = source[0] - target[0];
    double dy = source[1] - target[1];
    double distance = std::sqrt(dx*dx + dy*dy) / 2;
    
    distances[source] = std::min(distances[source], distance);
    distances[target] = std::min(distances[target], distance);
  }
  
  std::vector<double> result;
  for(auto el : distances) {
    result.push_back(el.second);
  }
  
  std::sort(result.begin(), result.end());
  int f = std::ceil(std::sqrt(result[0] - 0.5));
  int m = std::ceil(std::sqrt(result[result.size() / 2] - 0.5));
  int l2 = std::ceil(std::sqrt(result[result.size() - 1] - 0.5));

  std::cout << f << " " << m << " " << l2 << "\n";
  
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
