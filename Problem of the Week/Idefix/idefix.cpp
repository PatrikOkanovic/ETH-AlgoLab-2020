#include <iostream>
#include <vector>
#include <utility>
#include <queue>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> 
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/squared_distance_2.h>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/pending/disjoint_sets.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;

typedef CGAL::Exact_predicates_inexact_constructions_kernel         K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>         Vb;
typedef CGAL::Triangulation_data_structure_2<Vb>                    Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                      Triangulation;
typedef Triangulation::Vertex_handle                                Vertex_handle;
typedef Triangulation::Finite_faces_iterator                        Face_iterator;

typedef std::tuple<K::FT, int, int> Edge;

int k_bones(const Triangulation & t, const long & s, std::priority_queue<Edge> pq, int n, const std::vector<std::vector<long>> & bones_to_check){

  boost::disjoint_sets_with_storage<> uf(n);
  std::vector<int> bones(n);
  int max_bones = 0;
  for(int i = 0; i < n; ++i){
    
    auto pointer = upper_bound(bones_to_check[i].begin(), bones_to_check[i].end(), s/4);
    int new_bones = (pointer == bones_to_check[i].end()) ? bones_to_check[i].size() : pointer-bones_to_check[i].begin();
    
    max_bones = std::max(max_bones, bones[i] = new_bones);
  }
  
  while(!pq.empty()) {
    Edge e = pq.top();
    pq.pop();
    
    K::FT d = std::get<0>(e);
    int u = std::get<1>(e);
    int v = std::get<2>(e);
    
    if(s >= d) {
      if(uf.find_set(u) != uf.find_set(v)){
        int num_bones_u = bones[uf.find_set(u)];
        int num_bones_v = bones[uf.find_set(v)];
        uf.union_set(u, v);
        max_bones = std::max(max_bones, bones[uf.find_set(u)] = num_bones_u + num_bones_v);
      }
    }
  
  }
  
  return max_bones;
}

void test_case() {
  int n, m, k;
  long s;
  std::cin >> n >> m >> s >> k;
  
  std::vector<std::pair<K::Point_2,int>> pts;
  for(int i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    pts.push_back(std::make_pair(K::Point_2(x, y), i));
  }

  Triangulation t;
  t.insert(pts.begin(), pts.end());

  std::vector<std::vector<long>> bones_to_check(n);
  std::vector<long> tries;

  for(int i = 0; i < m; ++i) {
    int x, y;
    std::cin >> x >> y;

    K::Point_2 p(x, y);
    Vertex_handle v = t.nearest_vertex(p);
    K::FT d = CGAL::squared_distance(v->point(), p);
    tries.push_back(4 * d);
    bones_to_check[v->info()].push_back(d);
  }

  for(int i = 0; i < n; i++) {
    sort(bones_to_check[i].begin(), bones_to_check[i].end());
  }

  std::priority_queue<Edge> pq;
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int u = e->first->vertex((e->second+1)%3)->info();
    int v = e->first->vertex((e->second+2)%3)->info();
    
    auto d = t.segment(e).squared_length();
    tries.push_back(d);
    pq.push(std::make_tuple(d, u, v));
  }
  
  std::sort(tries.begin(), tries.end()); 
  
  std::cout << k_bones(t, s, pq, n, bones_to_check) << " ";
  
  int L = 0;
  int R = tries.size() - 1;
  
  while (L < R) {
    int mid = (L + R)/2;
    
    if(k_bones(t, tries[mid], pq, n, bones_to_check) < k) L = mid + 1;
    else R = mid;
    
  }
  
  std::cout << tries[L] << std::endl;
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  for(int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
