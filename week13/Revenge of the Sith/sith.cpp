#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;

typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;

std::vector<std::pair<K::Point_2, int> > pts;

bool check(int k, int r) {
  Triangulation t;
  t.insert(pts.begin() + k, pts.end());
  
  long rr = (long)r*r;
  
  graph G((int)pts.size() - k);
  for(auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    auto edge = *e;
    auto vertex1 = edge.first->vertex((edge.second + 1) % 3);
    auto vertex2 = edge.first->vertex((edge.second + 2) % 3);
    
    int i1 = vertex1->info();
    int i2 = vertex2->info();
    
    if(CGAL::squared_distance(vertex1->point(), vertex2->point()) <= rr) {
      boost::add_edge(i1 - k, i2 - k, G);
    }
  }
  
  std::vector<int> component_map((int)pts.size() - k);
  int ncc = boost::connected_components(G, boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G))); 
  
  std::vector<int> freq(ncc);
  for(int i = 0; i < (int)pts.size() - k; ++i) {
    freq[component_map[i]]++;
  }
  
  return *std::max_element(freq.begin(), freq.end()) >= k;
}

void test_case() {
  int n, r;
  std::cin >> n >> r;
  
  pts.clear();
  
  for(int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    K::Point_2 p(x, y);
    pts.push_back({p, i});
  }
  
  int L = 1, R = n/2 + 1;
  int solution;
  
  while(L <= R) {
    int mid = L + (R-L)/2;
    if(check(mid, r)) {
      L = mid + 1;
      solution = mid;
    } else {
      R = mid - 1;
    }
  }
  
  std::cout << solution << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  for(int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}

