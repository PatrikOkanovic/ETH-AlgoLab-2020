#include <iostream>
#include <vector>
#include <algorithm>

bool possible(int r, std::vector<int>& s, std::vector<int>& w) {
  int people_pointer = 0;
  int box_pointer = 0;

  while(people_pointer < (int)s.size() && box_pointer < (int)w.size()) {
    if(w[box_pointer] <= s[people_pointer]) {
      people_pointer++;
      box_pointer += r; // the person will carry the following r boxes in r rounds
    } else {
      return false;
    }
  }

  return box_pointer >= (int)w.size();
}

void test_case() {
  int n, m;
  std::cin >> n >> m;
  
  int max_w = -1, max_s = -1;
  std::vector<int> s(n);
  for(int i = 0; i < n; ++i) {
    std::cin >> s[i];
    max_s = std::max(max_s, s[i]);
  }
  std::sort(s.rbegin(), s.rend());

  std::vector<int> w(m);
  for(int i = 0; i < m; ++i) {
    std::cin >> w[i];
    max_w = std::max(max_w, w[i]);
  }
  
  if(max_w > max_s) {
    std::cout << "impossible\n";
    return;
  }
  
  std::sort(w.rbegin(), w.rend());

  // binary search for r
  int L = 1;
  int R = m;
  while(L < R) {
    int mid = (L + R) / 2;
    if(possible(mid, s, w)) R = mid;
    else L = mid + 1;
  }

  std::cout << 3*L - 1 << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  for(int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
