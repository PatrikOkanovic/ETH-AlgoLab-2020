#include <iostream>
#include<vector>
#include<map>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp> 


typedef boost::property<boost::edge_weight_t, int>                     EdgeWeightProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, EdgeWeightProperty >                            weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type   weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor              edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor            vertex_desc;


int dijsktra_dist(const weighted_graph& G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);
  
  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
    
  return dist_map[t];
}

void test_case() {
  int n, m, k, x, y;
  std:: cin >> n >> m >> k >> x >> y;
  
  weighted_graph G(n);

  for (int i = 0; i < m; ++i) {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    if (d) { // river
      for (int j = 0; j < k; ++j) {
        boost::add_edge(j*n + a, (j+1)*n + b, EdgeWeightProperty(c), G);
        boost::add_edge(j*n + b, (j+1)*n + a, EdgeWeightProperty(c), G);
      }
      boost::add_edge(k*n + a, k*n + b, EdgeWeightProperty(c), G);
      boost::add_edge(k*n + b, k*n + a, EdgeWeightProperty(c), G);
    } else {
      for (int j = 0; j <= k; ++j) {
        boost::add_edge(j*n + a, j*n + b, EdgeWeightProperty(c), G);
        boost::add_edge(j*n + b, j*n + a, EdgeWeightProperty(c), G);
      }
    }
    
  }
  
  int from = x;
  int to = k*n + y;
  
  std::cout << dijsktra_dist(G, from, to) << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}

