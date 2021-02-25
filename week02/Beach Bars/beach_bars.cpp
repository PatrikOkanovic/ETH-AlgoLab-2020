#include <iostream>
#include <vector>
#include <set>
#include <climits>

using namespace std;

int longest_distance(int a, int b) {
  int diff = b - a;
  if (diff % 2 == 0) return diff / 2;
  return diff / 2 + 1;
}

void test_case() {
  int n;
  cin >> n;
  set<int> s;
  for (int i = 0; i < n; i++) {
    int xi;
    cin >> xi;
    s.insert(xi);
  }

  vector<int> x(s.begin(), s.end());
  int i = 0, j = 0;
  vector<pair<int, int>> coordinates;
  int max_parasols = 0;
  int current_parasols = 0;
  int min_distance = INT_MAX;

  while (j < n) {
    if (x[j] - x[i] <= 200) {
      current_parasols++;
      if (current_parasols > max_parasols) {
        coordinates.clear();
        max_parasols = current_parasols;
        coordinates.push_back(make_pair(x[i], x[j]));
        min_distance = longest_distance(x[i], x[j]);

      } else if (current_parasols == max_parasols) {
        if (longest_distance(x[i], x[j]) == min_distance) {
          coordinates.push_back(make_pair(x[i], x[j]));
        } else if (longest_distance(x[i], x[j]) < min_distance) {
          coordinates.clear();
          coordinates.push_back(make_pair(x[i], x[j]));
          min_distance = longest_distance(x[i], x[j]);
        }
      }
      j++;

    } else {
      i++;
      current_parasols--;
    }
  }

  cout << max_parasols << " " << min_distance << "\n";
  for (auto p : coordinates) {
    if ((p.first + p.second) % 2 == 0) {
      cout << (p.first + p.second) / 2 << " ";
    } else {
      if (p.first + p.second > 0)
        cout << (p.first + p.second) / 2 << " " << (p.first + p.second) / 2 + 1
             << " ";
      else
        cout << (p.first + p.second) / 2 - 1 << " " << (p.first + p.second) / 2
             << " ";
    }
  }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
