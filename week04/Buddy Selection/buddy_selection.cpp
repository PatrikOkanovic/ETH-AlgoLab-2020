#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>
    graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;

void test_case() {
  int n, c, f;
  std::cin >> n >> c >> f;

  std::vector<std::set<std::string>> characteristics(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < c; ++j) {
      std::string s;
      std::cin >> s;
      characteristics[i].insert(s);
    }
  }

  graph G(n);

  for (int i = 0; i < n - 1; ++i) {
    std::vector<std::string> v(c);
    for (int j = i + 1; j < n; ++j) {
      auto it = std::set_intersection(
          characteristics[i].begin(), characteristics[i].end(),
          characteristics[j].begin(), characteristics[j].end(), v.begin());
      if (it - v.begin() > f) {
        // std::cout << i << " " << j << "\n";
        boost::add_edge(i, j, G);
      }
    }
  }

  std::vector<vertex_desc> mate_map(n);  // exterior property map
  boost::edmonds_maximum_cardinality_matching(
      G, boost::make_iterator_property_map(mate_map.begin(),
                                           boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(
      G, boost::make_iterator_property_map(mate_map.begin(),
                                           boost::get(boost::vertex_index, G)));
  // std::cout << matching_size << "\n";
  if (matching_size == n / 2)
    std::cout << "not optimal\n";
  else
    std::cout << "optimal\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;

  for (int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
