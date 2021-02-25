// STL includes
#include <iostream>
#include <vector>
#include <limits>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

// BGL Graph definitions
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                              boost::allow_parallel_edge_tag,
                              boost::property<boost::edge_weight_t, int>> Graph;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::property<boost::edge_weight_t, int>>
    WeightedGraph;

typedef boost::property_map<Graph, boost::edge_weight_t>::type
    WeightMap;  // property map to access the interior property edge_weight_t
typedef boost::graph_traits<WeightedGraph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

void addEdge(int from, int to, int w, WeightMap &weightmap, Graph &G) {
  Edge e;
  bool success;
  boost::tie(e, success) = boost::add_edge(from, to, G);
  weightmap[e] = w;
}

void test_case() {
  int n, m, a, s, c, d;
  std::cin >> n >> m >> a >> s >> c >> d;

  Graph G(n);
  WeightMap weightmap = boost::get(boost::edge_weight, G);

  for (int i = 0; i < m; ++i) {
    int x, y, z;
    char w;
    std::cin >> w >> x >> y >> z;
    addEdge(x, y, z, weightmap, G);
    if (w == 'L') addEdge(y, x, z, weightmap, G);
  }

  std::vector<std::vector<int>> dist_map(a, std::vector<int>(n));
  for (int agent = 0; agent < a; ++agent) {
    int alpha;
    std::cin >> alpha;
    boost::dijkstra_shortest_paths(
        G, alpha,
        boost::distance_map(boost::make_iterator_property_map(
            dist_map[agent].begin(), boost::get(boost::vertex_index, G))));
  }

  std::vector<std::vector<int>> times(a, std::vector<int>(s));
  for (int shelter = 0; shelter < s; ++shelter) {
    int sigma;
    std::cin >> sigma;
    for (int agent = 0; agent < a; ++agent) {
      times[agent][shelter] = dist_map[agent][sigma];
    }
  }

  int L = 0, R = std::numeric_limits<int>::max();
  while (L < R) {
    int mid = L + (R - L) / 2;
    WeightedGraph bipartite(a + c * s);
    for (int agent = 0; agent < a; ++agent) {
      for (int shelter = 0; shelter < s; ++shelter) {
        if (times[agent][shelter] == std::numeric_limits<int>::max()) continue;
        for (int capacity = 0; capacity < c; ++capacity) {
          if (times[agent][shelter] + (capacity + 1) * d <= mid) {
            boost::add_edge(agent, a + capacity * s + shelter, bipartite);
          }
        }
      }
    }
    std::vector<Vertex> matemap(a + c * s);
    boost::edmonds_maximum_cardinality_matching(
        bipartite, boost::make_iterator_property_map(
                       matemap.begin(), get(boost::vertex_index, bipartite)));
    int matching = boost::matching_size(
        bipartite,
        boost::make_iterator_property_map(
            matemap.begin(), boost::get(boost::vertex_index, bipartite)));
    if (matching == a) {
      R = mid;
    } else {
      L = mid + 1;
    }
  }
  std::cout << L << "\n";
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
