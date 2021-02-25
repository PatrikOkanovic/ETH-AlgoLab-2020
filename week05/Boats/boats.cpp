#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Boat {
  int p;
  int l;
  Boat (int _l, int _p) : l(_l), p(_p) {}
};

bool pos_sort(const Boat& b1, const Boat& b2) {
  return b1.p < b2.p;
}


void test_case() {
  int n; cin >> n;
  
  vector<Boat> boats;
  for (int i = 0; i < n; ++i) {
    int l, p; cin >> l >> p;
    Boat b (l, p);
    boats.push_back(b);
  }

  sort(boats.begin(), boats.end(), pos_sort);

  int num = 0;
  int current_end = boats[0].p - boats[0].l;
  int previous_end = current_end;
  for(int i = 0; i < n; ++i) {
    int li = boats[i].l;
    int pi = boats[i].p;
    if (current_end <= pi) {
      num++;
      previous_end = current_end;
      current_end = max (current_end + li, pi); // current_end + li => ring not at the end of the current boat
    } else {
      int alternative_end = max(previous_end + li, pi);
      current_end = min(alternative_end, current_end);
    }
  }

  cout << num << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  
  for (int i = 0; i < t; ++i) {
    test_case();
  }
  
}
