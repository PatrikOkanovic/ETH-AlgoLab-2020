#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool bomb_sort (const pair<int, int>& p1, const pair<int, int>& p2) {
  return p1.second < p2.second;
}

vector<bool> deactivated;
int n;
vector<int> bomb_time;
int current_time;

bool enough_time(int index) {
  if (deactivated[index]) return true;
  if (index >= (n-1)/2) {
    if (current_time < bomb_time[index]) {
      current_time++;
      deactivated[index] = true;
      return true;
    }
    
    return false;
  }
  
  if (current_time >= bomb_time[index]) return false;
  
  if (enough_time(2*index+1) && enough_time(2*index+2)) {
    if (current_time < bomb_time[index]) {
      current_time++;
      deactivated[index] = true;
      return true;
    }    
  }
  
  return false;
}

void test_case() {
  cin >> n;
  
  vector<pair<int, int> > bombs;
  bomb_time = vector<int> (n);
  for (int i = 0; i < n; ++i) {
    int ti; cin >> ti;
    bombs.push_back(make_pair(i, ti));
    bomb_time[i] = ti;
  }
  
  current_time = 0;
  deactivated = vector<bool> (n, false);
  
  sort(bombs.begin(), bombs.end(), bomb_sort);
  
  bool enough = true;
  for (int i = 0; i < n; ++i) {
    if (!enough_time(bombs[i].first)) {
      enough = false;
      break;
    }
  }
  
  if (enough) cout << "yes\n";
  else cout << "no\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  
  for (int i = 0; i < t; ++i) {
    test_case();
  }
  
  return 0;
}
