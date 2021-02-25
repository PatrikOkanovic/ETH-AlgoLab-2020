#include<iostream>
#include <vector>

using namespace std;

void test_case() {
    int n; cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    int max = h[0];

    int i;
    for(i = 1; i < n; i++) {
        if (max <= i) break;
        max = std::max(max, h[i] + i);
    }
    cout << i << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for(int i = 0; i < t; i++) {
        test_case();
    }
}
