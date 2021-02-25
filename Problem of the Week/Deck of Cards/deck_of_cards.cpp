#include <iostream>
#include <vector>

using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }

  pair<int, int> result;

  int left = 0, right = 0;
  int sum = v[0];
  result.first = left;
  result.second = right;

  int minVal = abs(k - sum);

  bool flag = true;

  while (sum != k && flag) {
    if (sum < k) {
      right++;
      sum += v[right];
      if (right >= n) flag = false;
    } else if (sum > k) {
      sum -= v[left];
      left++;
    }

    int diff = abs(k - sum);
    if (diff < minVal) {
      minVal = diff;
      result.first = left;
      result.second = right;
    }
  }

  cout << result.first << " " << result.second << "\n";
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

