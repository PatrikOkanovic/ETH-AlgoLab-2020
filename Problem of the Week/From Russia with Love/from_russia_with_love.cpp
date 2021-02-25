#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int n, m, k;
vector<int> x;
vector<vector<int>> memo;

int f(int windowOffset, int windowLength, int opponentCount) {
  if (windowLength <= 0) return 0;

  if (memo[windowOffset][windowLength] != -1)
    return memo[windowOffset][windowLength];

  int nextWindowLength = windowLength - opponentCount - 1;

  int minAfterLeft = INT_MAX;

  for (int i = windowOffset + 1; i <= windowOffset + 1 + opponentCount; i++) {
    minAfterLeft = min(minAfterLeft, f(i, nextWindowLength, opponentCount));
  }

  int minAfterRight = INT_MAX;

  for (int i = windowOffset; i <= windowOffset + opponentCount; i++) {
    minAfterRight = min(minAfterRight, f(i, nextWindowLength, opponentCount));
  }

  int maxProfitForMove =
      max(x[windowOffset] + minAfterLeft,
          x[windowOffset + windowLength - 1] + minAfterRight);

  memo[windowOffset][windowLength] = maxProfitForMove;

  return maxProfitForMove;
}

void test_case() {
  cin >> n >> m >> k;

  x = vector<int>(n);

  for (int i = 0; i < n; i++) {
    cin >> x[i];
  }

  memo = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));

  int minV = INT_MAX;

  for (int i = 0; i <= k; i++) {
    minV = min(minV, f(i, n - k, (m - 1)));
  }

  cout << minV << "\n";
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
