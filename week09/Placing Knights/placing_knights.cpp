// Includes
// ========
// STL includes
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

// BGL graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef  boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
  boost::property<boost::edge_capacity_t, long,
    boost::property<boost::edge_residual_capacity_t, long,
      boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >  graph;
// Interior Property Maps
typedef  boost::graph_traits<graph>::edge_descriptor      edge_desc;
typedef  boost::graph_traits<graph>::out_edge_iterator      out_edge_it;
typedef boost::graph_traits<graph>::vertex_descriptor     vertex_desc;

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void test_case() {
  int n; std::cin >> n;
  
  std::vector<std::vector<int> > available (n, std::vector<int>(n));
  int holes = 0;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      std::cin >> available[i][j];
      if(!available[i][j]) holes++;
    }
  }
  
  graph G(n*n);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_sink = boost::add_vertex(G);
  edge_adder adder(G);
  // auto rc_map = boost::get(boost::edge_residual_capacity, G);
  
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      int current = n*i + j;
      if((i+j)%2 == 0 && available[i][j]) {
        adder.add_edge(v_source, current, 1);
        // [i−1,j−2]
        if(i - 1 >= 0 && j - 2 >= 0 && available[i - 1][j - 2]) {
          adder.add_edge(current, j - 2 + n * (i - 1), 1);
        }
        // [i−1,j+2]
        if(i - 1 >= 0 && j + 2 < n && available[i - 1][j + 2]) {
          adder.add_edge(current, j + 2 + n * (i - 1), 1);
        }
        // [i+1,j−2]
        if(i + 1 < n && j - 2 >= 0 && available[i + 1][j - 2]) {
          adder.add_edge(current, j - 2 + n * (i + 1), 1);
        }
        // [i+1,j+2]
        if(i + 1 < n && j + 2 < n && available[i + 1][j + 2]) {
          adder.add_edge(current, j + 2 + n * (i + 1), 1);
        }
        // [i−2,j−1]
        if(i - 2 >= 0 && j - 1 >= 0 && available[i - 2][j - 1]) {
          adder.add_edge(current, j - 1 + n * (i - 2), 1);
        }
        // [i−2,j+1]
        if(i - 2 >= 0 && j + 1 < n && available[i - 2][j + 1]) {
          adder.add_edge(current, j + 1 + n * (i - 2), 1);
        }
        // [i+2,j−1]
        if(i + 2 < n && j - 1 >= 0 && available[i + 2][j - 1]) {
          adder.add_edge(current, j - 1 + n * (i + 2), 1);
        }
        // [i+2,j+1]
        if(i + 2 < n && j + 1 < n && available[i + 2][j + 1]) {
          adder.add_edge(current, j + 1 + n * (i + 2), 1);
        }
      } else {
        adder.add_edge(current, v_sink, 1);
      }
    }
  }
  
  int flow = boost::push_relabel_max_flow(G, v_source, v_sink);
  
  std::cout << n*n - holes - flow << "\n";

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  for(int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}
