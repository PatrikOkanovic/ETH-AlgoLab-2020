// Includes
// ========
// STL includes
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/graph/strong_components.hpp>

// BGL Graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef  boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
      boost::property<boost::edge_reverse_t, Traits::edge_descriptor> > > >  Graph;
// Interior Property Maps
typedef  boost::property_map<Graph, boost::edge_capacity_t>::type    EdgeCapacityMap;
typedef  boost::property_map<Graph, boost::edge_residual_capacity_t>::type  ResidualCapacityMap;
typedef  boost::property_map<Graph, boost::edge_reverse_t>::type    ReverseEdgeMap;
typedef  boost::graph_traits<Graph>::edge_descriptor      Edge;


// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class EdgeAdder {
  Graph &G;
  EdgeCapacityMap  &capacitymap;
  ReverseEdgeMap  &revedgemap;

public:
  // to initialize the Object
  EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
    G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

  // to use the Function (add an edge)
  void addEdge(int from, int to, long capacity) {
    Edge e, rev_e;
    bool success;
    boost::tie(e, success) = boost::add_edge(from, to, G);
    boost::tie(rev_e, success) = boost::add_edge(to, from, G);
    capacitymap[e] = capacity;
    capacitymap[rev_e] = 0; // reverse edge has no capacity!
    revedgemap[e] = rev_e;
    revedgemap[rev_e] = e;
  }
};

void test_case() {
  int n,m;
  std::cin >> n >> m;

  // Create Graph and Maps
  Graph G(n);
  EdgeCapacityMap capacitymap = boost::get(boost::edge_capacity, G);
  ReverseEdgeMap revedgemap = boost::get(boost::edge_reverse, G);
  // ResidualCapacityMap rescapacitymap = boost::get(boost::edge_residual_capacity, G);
  EdgeAdder adder(G, capacitymap, revedgemap);

  for(int i = 0; i < m; ++i){
    int a, b, c;
    std::cin >> a >> b >> c;
    adder.addEdge(a, b, c);
  }

  long min_max_flow = std::numeric_limits<long>::max();
  for(int source = 0; source < n; ++source){
    int target = (source + 1) % n;
    long flow = boost::push_relabel_max_flow(G, source, target);
    if(flow < min_max_flow){
      min_max_flow = flow;
    }
  }

  std::cout << min_max_flow << "\n";

}


int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for(int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}
