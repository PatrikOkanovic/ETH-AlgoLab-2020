#include <iostream>
#include <algorithm>
#include <vector>

#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;


int furthest_node(const weighted_graph &G,int  s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);
  
  boost:dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(dist_map.begin(),
          boost::get(boost::vertex_index, G))));

  return *std::max_element(dist_map.begin(), dist_map.end());  
}

int sum_min_spanning_tree(const weighted_graph &G) {
  std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)

  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));


  int sum = 0;

  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    sum += boost::get(boost::edge_weight, G, *it);
  }

  return sum;
}

void test_case() {
  int n, m;
  std::cin >> n >> m;

  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;

  for(int i = 0; i < m; ++i) {
    int source, target, weight;
    std::cin >> source >> target >> weight;
    e = boost::add_edge(source, target, G).first; 
    weights[e] = weight;
  }

  std::cout << sum_min_spanning_tree(G) << " " << furthest_node(G, 0) << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  for(int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}

