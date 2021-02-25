#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void ispisi(vector<vector<pair<int, int> > >& dp, int n, int k) {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= k; ++j) {
      cout << "(" << dp[i][j].first << "," << dp[i][j].second << ")"
           << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> c(n + 1), v(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> c[i] >> v[i];
  }

  vector<vector<pair<int, int> > > dp(n + 1, vector<pair<int, int> >(k + 1));

  for (int i = 0; i <= n; ++i) {
    dp[i][0] = {0, 0};
  }

  for (int i = 1; i <= k; ++i) {
    dp[0][i] = {10e8, -1};
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= k; ++j) {
      dp[i][j] = dp[i - 1][j];

      for (int it = 0; it < 2; ++it) {
        auto x = dp[i - it][max(0, j - v[i])];
        if (c[i] + x.first < dp[i][j].first) {
          dp[i][j].first = c[i] + x.first;
          dp[i][j].second = it + x.second;
        } else if (c[i] + x.first == dp[i][j].first) {
          dp[i][j].second = max(dp[i][j].second, it + x.second);
        }
      }
      // ispisi(dp, n, k);
    }
  }

  cout << dp[n][k].first << " " << dp[n][k].second << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false );
  int t;
  std::cin >> t;

  for (int i = 0; i < t; ++i) {
    test_case();
  }

  return 0;
}
