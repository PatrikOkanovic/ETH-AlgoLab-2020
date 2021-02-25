#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int, long> > > graph;

vector<vector<long>> memo;

long f(int node, int steps_left) {
  if (steps_left == 0) return 0;
  long max_sum = 0;
  if (memo[node][steps_left] != -1) return memo[node][steps_left];
  if (graph[node].size() == 0) {
    max_sum = f(0, steps_left);
  } else {
    for (auto& p : graph[node]) {
      max_sum = max(max_sum, p.second + f(p.first, steps_left - 1));
    }
  }
  
  memo[node][steps_left] = max_sum;
  
  return max_sum;
}

void test_case() {
  int n, m, k;
  long x;
  cin >> n >> m >> x >> k;
  
  graph = vector<vector<pair<int, long>>>(n, vector<pair<int, long>>(0));
  for (int i = 0; i < m; ++i) {
    int u, v;
    long p;
    cin >> u >> v >> p;
    
    graph[u].push_back(make_pair(v, p));    
  }
  
  memo = vector<vector<long>> (n, vector<long> (k+1, -1));
  
  
  int steps;
  for (steps = 1; steps <= k; ++steps) {
    if (f(0, steps) >= x) break;
  }
  
  if (steps <= k) cout << steps << "\n";
  else cout << "Impossible\n";  
  
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  
  for (int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}
