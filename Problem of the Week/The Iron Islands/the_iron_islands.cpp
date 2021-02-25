#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int slide_window(vector<int>& path, int k, vector<int>& c){
  int n = path.size();

  int left = 0;
  int right = 0;
  int sum = 0;
  int max_len = 0;
  while(true){
    if(sum == k){
      max_len = max(max_len, right - left);
      sum -= c[path[left++]];
    } 
    else if(sum > k){
      sum -= c[path[left++]];
    }
    else{
      if(right == n) break;
      sum += c[path[right++]];
    }
    
    if(left > right){
      right = left;
      sum = c[path[left]];
    }
  
  }
  
  return max_len;
}

void test_case() {
  int n, w, k;
  std::cin >> n >> k >> w;
  
  vector<int> c(n);
  for(int i = 0; i < n; ++i) {
    cin >> c[i];
  }
  
  vector<vector<int>> w_i(w, vector<int>());
  for(int i = 0; i < w; ++i) {
    int l; cin >> l;
    for(int j = 0; j < l; ++j) {
      int r; cin >> r;
      w_i[i].push_back(r);
    }
  }
  
  int max_len = 0;
  for(int i = 0; i < (int)w_i.size(); ++i) {
    max_len = max(max_len, slide_window(w_i[i], k, c));
  }

  unordered_map<int, int> map;
  vector<int> sums(n);
  for(int i = 0; i < w; ++i) {
    sums.resize(1);
    int partial_sum = 0;
    for(int j = 1; j < (int)w_i[i].size(); ++j) {
      partial_sum += c[w_i[i][j]];
      if(partial_sum >= k) break;
      sums.push_back(partial_sum);
    }

    for(int j = 1; j < (int)sums.size(); ++j) {
      auto it = map.find(k - sums[j] - c[0]);
      if(it != std::end(map)) {
        max_len = max(max_len, it->second + j + 1);
      }
    }

    for(int j = 1; j < (int)sums.size(); ++j) {
      auto it = map.find(sums[j]);
      if(it != std::end(map)) {
        it->second = max(it->second, j);
      } else {
        map.insert({sums[j], j}); 
      }
    }
  }
  
  cout << max_len << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  for(int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}
