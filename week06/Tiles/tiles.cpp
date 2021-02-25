#include <iostream>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

int maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n);  // exterior property map

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  
  return matching_size;
  
}

int w, h;

int num_vertex(int row, int column) {
  return w*row + column;
}

void test_case() {
  std::cin >> w >> h;
  
  int dots = 0;  
  std::vector<std::vector<char>> garden (h, std::vector<char> (w));
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      std::cin >> garden[i][j];
      if (garden[i][j] == '.') dots++;
    }
  }
  
  // Build the graph
  graph G(dots);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      // Connect right and down
      if (garden[i][j] == 'x') continue;
      if (i != h-1 && garden[i+1][j] != 'x') boost::add_edge(num_vertex(i, j), num_vertex(i+1, j), G);
      if (j != w-1 && garden[i][j+1] != 'x') boost::add_edge(num_vertex(i, j), num_vertex(i, j+1), G);
    }
  }
  
  int matching_size = maximum_matching(G);
  if (2*matching_size == dots) std::cout << "yes\n";
  else std::cout << "no\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  for (int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}
