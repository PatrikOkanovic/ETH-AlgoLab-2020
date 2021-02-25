#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> memo;

int f(vector<int> &v, int i, int j) {
    if (i > j) return 0;
    if (i == j) return v[i];

    if (memo[i][j] != 0) return memo[i][j];

    int first = v[i] + min(f(v, i+2, j), f(v, i+1, j-1));
    int second = v[j] + min(f(v, i, j-2), f(v, i+1, j-1));

    memo[i][j] = max(first, second);
    return max(first, second);
}

void test_case() {
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    memo = vector<vector<int>> (n, vector<int>(n));
    cout << f(v, 0, n -1) << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        test_case();
    }

    return 0;
}
