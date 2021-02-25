#include <iostream>
#include <vector>
#include <algorithm> 

// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;


// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};


void test_case() {

  long n, m, s;
  std::cin >> n >> m >> s;
  
  std::vector<long> si (s);
  for (long i = 0; i < s; ++i) {
    std::cin >> si[i];
  }

  graph G(n);
  edge_adder adder(G);

  long source_capacity = 0;
  for (long i = 0; i < m; ++i) {
    long u, v;
    std:: cin >> u >> v;
    if (u > v) std::swap(u, v);
    if (u == 0) source_capacity++;
    adder.add_edge (u, v, 1);
    adder.add_edge (v, u, 1);
    
  }
  
  // Add special vertices source and sink
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  adder.add_edge(v_source, 0, source_capacity);

  for (long i = 0; i < s; ++i) {
    adder.add_edge(si[i], v_sink, 1);
  }

  // Calculate flow from source to sink
  // The flow algorithm uses the interior properties (managed in the edge adder)
  // - edge_capacity, edge_reverse (read access),
  // - edge_residual_capacity (read and write access).
  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);

  if (flow < s) std::cout << "no\n";
  else std::cout << "yes\n";
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  for (int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;

}
