#include <iostream>
#include <algorithm>
#include <limits>
#include <boost/pending/disjoint_sets.hpp>

struct Edge {
  int first, second, cost;
  
  Edge(int f, int s, int c) : first(f), second(s), cost(c) {};
};

bool my_sort(const Edge& a, const Edge& b) {
  if(a.cost == b.cost) return std::max(a.first, a.second) > std::max(b.first, b.second);
  return a.cost < b.cost;
}

int mst(int n, std::vector<Edge>& edges, std::vector<int>& used_edges, int remember_used, int ignored) {
  boost::disjoint_sets_with_storage<> uf(n);
  int cost = 0;
  for(int i = 0; i < (int)edges.size(); ++i) {
    int comp1 = uf.find_set(edges[i].first);
    int comp2 = uf.find_set(edges[i].second);    
    
    if(comp1 != comp2 && i != ignored) {
      uf.link(comp1, comp2);
      if(remember_used) used_edges.push_back(i);
      cost += edges[i].cost;
      if(--n == 1) break;
    }
  }

  return cost;
}

void test_case() {
  int n, tatooine;
  std::cin >> n >> tatooine;
  std::vector<Edge> edges;
  for(int j = 0; j < n - 1; ++j) {
    for(int k = j+1; k < n; ++k) {
      int cost; std::cin >> cost;
      edges.push_back(Edge(j, k, cost));
    }
  }

  std::sort(edges.begin(), edges.end(), my_sort);
  
  std::vector<int> used_edges;
  mst(n, edges, used_edges, true, -1);

  int min_mst = std::numeric_limits<int>::max();

  for(int i = 0; i < (int)used_edges.size(); ++i) {
    int ignored = used_edges[i]; 
    min_mst = std::min(min_mst, mst(n, edges, used_edges, false, ignored));
  }

  std::cout << min_mst << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;

  for(int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
