#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

using namespace boost;

typedef adjacency_list < vecS, vecS, undirectedS,
    no_property, property<edge_index_t, int> >graph_t;
typedef graph_traits < graph_t >::vertex_descriptor vertex_t;


void test_case() {
  int n, m;
  std::cin >> n >> m;
  graph_t g(n);
  
  for (int i = 0; i < m; ++i) {
    int e1, e2;
    std::cin >> e1 >> e2;
    add_edge(e1, e2, g);
  }

  property_map < graph_t, edge_index_t >::type component = get(edge_index, g);

  int num_comps = biconnected_components(g, component);

  std::vector<int> freq (num_comps);
  
  std::unordered_map<int, std::pair<int, int>> map;
  graph_traits < graph_t >::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    freq[component[*ei]]++;  
    //std::cout << source(*ei, g) << target(*ei, g) << " " << component[*ei] << "\n";
    int i = std::min(source(*ei, g), target(*ei, g));
    int j = std::max(source(*ei, g), target(*ei, g));
    map.insert({component[*ei], {i, j}});
  }
  std::vector<std::pair<int, int>> result;
  
  for (int comp = 0; comp < freq.size(); ++comp) {
    if (freq[comp] == 1) {
      result.push_back(map[comp]);
    }
  }

  std::sort(result.begin(), result.end());

  std::cout << result.size() << "\n";
  for (int i = 0; i < result.size(); ++i) {
    std::cout << result[i].first << " " << result[i].second << "\n";
  }
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int c; std::cin >> c;

  for(int i = 0; i < c; ++i) {
    test_case();
  }
}
