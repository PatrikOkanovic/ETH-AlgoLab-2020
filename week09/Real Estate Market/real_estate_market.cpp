// Includes
// ========
#include <iostream>
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

int n, m, s;
const int delta = 100;

int ordinal_buyer(int buyer) {
  return 1 + buyer;
}

int ordinal_site(int site) {
  return 1 + n + site; 
}

int ordinal_state(int state) {
  return 1 + n + m + state;
}

int transform_cost(int b) {
  return -b + delta;
}

int final_cost(int cost, int sold_estates) {
  return sold_estates*delta - cost;
}

void test_case() {
  std::cin >> n >> m >> s;

  // Create graph, edge adder class and propery maps
  graph G(n + m + s + 2);
  edge_adder adder(G);  
  auto c_map = boost::get(boost::edge_capacity, G);
  // auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);

  const int v_source = 0;
  const int v_target = n + m + s + 1;

  for(int i = 0; i < s; ++i) {
    int l; std::cin >> l;
    // connect states with sink
    adder.add_edge(ordinal_state(i), v_target, l, 0);
  }

  for(int i = 0; i < m; ++i) {
    int si; std::cin >> si;
    si--; // si starts from 1, not from 0
    // connect sites with states
    adder.add_edge(ordinal_site(i), ordinal_state(si), 1, 0);
  }

  for(int i = 0; i < n; ++i) {
    // connect source with buyers 
    adder.add_edge(v_source, ordinal_buyer(i), 1, 0);
    for(int j = 0; j < m; ++j) {
      int b_ij; std::cin >> b_ij;
      // connect buyers with site
      adder.add_edge(ordinal_buyer(i), ordinal_site(j), 1, transform_cost(b_ij));
    }
  }

  // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights  
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
  int cost = boost::find_flow_cost(G);

  // Or equivalently, you can do the summation at the sink, but with reversed edge.
     // Or equivalently, you can do the summation at the sink, but with reversed edge.
  int flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_target,G), G); e != eend; ++e) {
    flow += rc_map[*e] - c_map[*e];  
  }

  std::cout << flow << " " << final_cost(cost, flow) << "\n";
  
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;

  for(int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
