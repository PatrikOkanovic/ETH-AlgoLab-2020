#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<vector<int>> children;
vector<int> path;
multiset<int> temps;
vector<int> temperature;
int n, m, k;
set<int> result;

void dfs(int pos) {
  path.push_back(pos);
  temps.insert(temperature[pos]);
  if(temps.size() > m) {
    int index_remove = path.rbegin()[m];
    auto it = temps.find(temperature[index_remove]);
    temps.erase(it);
  }
  if(temps.size() == m) {
    int max = *temps.rbegin();
    int min = *temps.begin();
    if(max - min <= k) {
      result.insert(path.rbegin()[m-1]);
    }
  }

  for(auto el : children[pos]) {
    dfs(el);
  }
  
  path.pop_back();
  auto it = temps.find(temperature[pos]);
  temps.erase(it);

  if(path.size() >= m) {
    int i = path.rbegin()[m-1];
    temps.insert(temperature[i]);
  }
}

void test_case() {
  cin >> n >> m >> k;

  temperature = vector<int>(n);
  for(int i = 0; i < n; ++i) {
    cin >> temperature[i];
  }

  children = vector<vector<int>>(n);
  for(int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    children[u].push_back(v);
  }

  path.clear();
  path.reserve(n);
  temps.clear();
  result.clear();

  dfs(0);

  if(result.size() != 0) {
    for(auto x : result) {
      cout << x << " ";
    }
    cout << "\n";
  } else {
    cout << "Abort mission\n";
  }
  
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  
  for(int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
