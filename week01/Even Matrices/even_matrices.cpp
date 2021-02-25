#include <iostream>
#include <vector>

using namespace std;

void test_case() {
  int n;
  cin >> n;
  vector<vector<int>> v(n, vector<int>(n));

  // (i,j) is the sum of rectangle from (0,0)
  vector<vector<int>> sums(n, vector<int>(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> v[i][j];
      sums[i][j] = (i > 0 ? sums[i - 1][j] : 0) + v[i][j];
    }
  }

  int result = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      int even = 1;
      int odd = 0;
      int current = 0;

      for (int k = 0; k < n; k++) {
        current += sums[j][k] - (i > 0 ? sums[i - 1][k] : 0);
        if (current % 2 == 0) {
          result += even;
          even++;
        } else {
          result += odd;
          odd++;
        }
      }
    }
  }

  cout << result << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    test_case();
  }

  return 0;
}
