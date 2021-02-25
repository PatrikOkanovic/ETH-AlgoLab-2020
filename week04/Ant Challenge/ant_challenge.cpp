#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property,
                              EdgeWeightProperty> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type
    weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

int dijsktra_dist(const weighted_graph& G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(
      G, s, boost::distance_map(boost::make_iterator_property_map(
                dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map[t];
}

void test_case() {
  int n, e, s, a, b;
  std::cin >> n >> e >> s >> a >> b;

  std::vector<weighted_graph> graphs(s, weighted_graph(n));

  for (int i = 0; i < e; ++i) {
    int t1, t2;
    std::cin >> t1 >> t2;
    for (int j = 0; j < s; ++j) {
      int w;
      std::cin >> w;
      boost::add_edge(t1, t2, EdgeWeightProperty(w), graphs[j]);
    }
  }

  weighted_graph G(n);
  for (int i = 0; i < s; ++i) {
    int h;
    std::cin >> h;  // should be of use in Prim's algorithm, but not with Kruskal
    std::vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(graphs[i], std::back_inserter(mst));

    for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
      int source = boost::source(*it, graphs[i]);
      int target = boost::target(*it, graphs[i]);
      int weight = boost::get(boost::edge_weight, graphs[i], *it);

      boost::add_edge(source, target, EdgeWeightProperty(weight), G);
    }
  }

  std::cout << dijsktra_dist(G, a, b) << "\n";
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
