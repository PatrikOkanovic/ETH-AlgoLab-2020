#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > connections;
vector<int> cost;
vector<int> memo_true;
vector<int> memo_false;

int dp_true(int position);

int dp_false(int position) {
  if (memo_false[position] != -1) return memo_false[position];
  if (connections[position].size() == 0) {
    memo_false[position] = cost[position];
    return memo_false[position];
  }
  
  int me_true = cost[position], all_childs_false = 0, me_false = -1;
  for(int i = 0; i < (int)connections[position].size(); ++i) {
    me_true += dp_true(connections[position][i]);
    all_childs_false += dp_false(connections[position][i]);
  }
  
  for (int i = 0; i < (int)connections[position].size(); ++i) {
    int grand_childs_true = 0;
    for (int j = 0; j < (int)connections[connections[position][i]].size(); ++j) {
      grand_childs_true += dp_true(connections[connections[position][i]][j]);
    }
    if(me_false == -1)
      me_false = grand_childs_true + all_childs_false - memo_false[connections[position][i]] + cost[connections[position][i]];
    else
      me_false = min(me_false, grand_childs_true + all_childs_false - memo_false[connections[position][i]] + cost[connections[position][i]]);
  }
  
  memo_false[position] = min(me_true, me_false);
  
  return memo_false[position];
}

int dp_true(int position) {
  if (memo_true[position] != -1) return memo_true[position];
  if (connections[position].size() == 0) {
    memo_true[position] = 0;
    return memo_true[position];
  }
  
  int me_true = cost[position], all_childs_false = 0;
  for(int i = 0; i < (int)connections[position].size(); ++i) {
    me_true += dp_true(connections[position][i]);
    all_childs_false += dp_false(connections[position][i]);
  }
  
  memo_true[position] = min(me_true, all_childs_false);
  
  return memo_true[position];
}


void test_case() {
  int n; cin >> n;
  
  connections = vector<vector<int> > (n);
  for(int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b;
    connections[a].push_back(b);
    //connections[b].push_back(a);
  }
  
  cost = vector<int>();
  for (int i = 0; i < n; ++i) {
    int ci; cin >> ci;
    cost.push_back(ci);
  }
  
  memo_true = vector<int> (n, -1);
  memo_false = vector<int> (n, -1);
  
  cout << dp_false(0) << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; cin >> t;
  
  for(int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}
