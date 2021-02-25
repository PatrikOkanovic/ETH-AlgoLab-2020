#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <set>

using namespace std;

void test_case() {
  int n; cin >> n;
  
  vector<int> m(n);
  set<pair<int, int>> s;
  for (int i = 0; i < n; ++i) {
    cin >> m[i];
  }
  
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m[i]; ++j) {
      int p_ij; cin >> p_ij;
      s.insert(make_pair(p_ij, i));
    }
  }
  
  vector<pair<int, int>> p (s.begin(), s.end());
  
  int a = 0;
  int b = 0;
  vector<int> word_freq(n, 0);
  word_freq[p[0].second] = 1;
  int words_in = 1;
  int min_distance = INT_MAX;
  
  while (b < p.size()) {
    if (words_in >= n) {
      min_distance = min(min_distance, p[b].first - p[a].first + 1);
      word_freq[p[a].second] -= 1;
      if (word_freq[p[a].second] == 0) words_in--;
      a++;
      
    } else {
      b++;
      word_freq[p[b].second] += 1;
      if (word_freq[p[b].second] == 1) words_in++; 
    }
  }
  
  cout << min_distance << "\n";
  
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  for (int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}
