#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

int binary(int b, const vector<int>& path, const vector<int>& age) {
  int L = -1;
  int R = path.size() - 1;
  
  while(L + 1 < R) {
    int mid = (L + R) / 2;
      
    if(age[path[mid]] <= b) R = mid;
    else L = mid;
  }
  
  return path[R];
}

void dfs(int u, vector<vector<int> >& tree, vector<int>& path, 
  const vector<vector<pair<int,int> > >& query, vector<int>& result,
  const std::vector<int>& age) {
  
  for(int i = 0; i < (int)query[u].size(); ++i) {
    result[query[u][i].second] = binary(query[u][i].first,path,age);
  }
  
  for(int i = 0; i < (int)tree[u].size(); ++i) {
    int v = tree[u][i];
    path.push_back(v);
    dfs(v,tree,path,query,result,age);
  }
  path.pop_back();     
}

void test_case() {
  int n, q;
  cin >> n >> q;
  
  unordered_map<std::string,int> species_to_index;
  vector<std::string> species(n);
  vector<int> age(n);
  
  int root = -1;
  int max_age = -1;
  for(int i = 0; i < n; ++i) {
    string name; 
    cin >> name >> age[i];
    species_to_index[name] = i;
    species[i] = name;
    if(max_age < age[i]) {
      max_age = age[i];
      root = i;
    }
  }
  
  vector<vector<int> > tree(n);
  for(int i = 0; i < n-1; ++i) {
    string child, parent; 
    cin >> child >> parent;
    tree[species_to_index[parent]].push_back(species_to_index[child]);
  }
  
  vector<std::vector<std::pair<int,int> > > query(n);
  for(int i = 0; i < q; ++i) {
    string name;
    int b;
    cin >> name >> b;
    query[species_to_index[name]].push_back(make_pair(b,i));
  }
  
  vector<int> path; path.push_back(root);
  vector<int> result(q);
  
  dfs(root,tree,path,query,result,age);
  
  for(int i = 0; i < q; ++i) {
    cout << species[result[i]] << " ";
  }
  cout << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; cin >> t;
  
  for(int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}