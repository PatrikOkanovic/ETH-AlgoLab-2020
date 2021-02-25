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

int n, m, k, c;

int in_edge(int row, int column) {
  return 2 * m * row + 2 * column;
}

int out_edge(int row, int column) {
  return 2 * m * row + 2 * column + 1;
}

void test_case() {
  std::cin >> m >> n >> k >> c;
  
  graph G(2 * n * m);
  edge_adder adder(G);

  // Add special vertices source and sink
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);

  // Connect source
  for (int i = 0; i < k; ++i) {
    int x, y;
    std::cin >> x >> y;
    adder.add_edge (v_source, in_edge(y, x), 1);
  }

  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < m; ++x) {
      int v_in = in_edge(y, x);
      int v_out = out_edge(y, x);
      adder.add_edge(v_in, v_out, c);
      if(x != 0) adder.add_edge(v_out, in_edge(y, x-1), 1);
      else adder.add_edge(v_out, v_sink, 1);
      if(y != 0) adder.add_edge(v_out, in_edge(y-1, x), 1);
      else adder.add_edge(v_out, v_sink, 1);
      if(x != m-1) adder.add_edge(v_out, in_edge(y, x+1), 1);
      else adder.add_edge(v_out, v_sink, 1);
      if(y != n-1)adder.add_edge(v_out, in_edge(y+1, x), 1);
      else adder.add_edge(v_out, v_sink, 1);
    }
  }

  long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  std::cout << flow << "\n";

  
}

int main () {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;

  for (int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
