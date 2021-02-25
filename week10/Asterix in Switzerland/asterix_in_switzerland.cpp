#include <iostream>

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
  int n, m;
  std::cin >> n >> m;

  graph G(n);

  auto source = boost::add_vertex(G);
  auto sink = boost::add_vertex(G);
  edge_adder adder(G);

  long sum = 0;

  for(int i = 0; i < n; ++i) {
    int b_i; std::cin >> b_i;
    if(b_i >= 0) {
      adder.add_edge(source, i, b_i);
      sum += b_i;
    } else {
      adder.add_edge(i, sink, -b_i);
    }
  }

  for(int k = 0; k < m; ++k) {
    int i, j, d_ij;
    std::cin >> i >> j >> d_ij;
    adder.add_edge(i, j, d_ij);
  }

  long flow = boost::push_relabel_max_flow(G, source, sink);  

  if(sum - flow > 0) std::cout << "yes\n";
  else std::cout << "no\n"; 

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;

  for(int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
