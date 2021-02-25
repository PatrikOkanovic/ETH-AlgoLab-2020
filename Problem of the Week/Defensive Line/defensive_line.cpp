#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<int> v(n + 1);

  for (int i = 1; i <= n; ++i) {
    cin >> v[i];
  }

  vector<int> attack(n, -1);  // attack[i]=-1 if attack cannot start at index i

  int l = 1, r = 1;
  int sum = v[1];
  while (r <= n) {
    if (sum == k) {
      attack[l] = r;
      sum -= v[l];
      l++;
    } else if (sum < k) {
      r++;
      sum += v[r];
    } else {  // sum > k
      sum -= v[l];
      l++;
    }
  }

  // dp[i][l] max attack value starting at position l with i attackers
  vector<vector<int>> dp(m + 1, vector<int>(n + 2, -1));  

  int a = n - 1;  // start filling dp from the back
  dp[0][n + 1] = 0;
  dp[0][n] = 0;
  if (v[n] == k) dp[1][n] = 1;

  while (a > 0) {
    dp[0][a] = 0;
    int b = attack[a];
    if (b == -1) {
      for (int i = 1; i <= m; ++i) {
        dp[i][a] = dp[i][a + 1];
      }
    } else {
      for (int i = 1; i <= m; ++i) {
        dp[i][a] = dp[i - 1][b + 1] == -1
                       ? dp[i][a + 1]
                       : max(dp[i][a + 1], (b - a + 1) + dp[i - 1][b + 1]);
      }
    }
    a--;
  }

  int result = dp[m][1];
  if (result != -1)
    cout << result << "\n";
  else
    cout << "fail\n";
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
