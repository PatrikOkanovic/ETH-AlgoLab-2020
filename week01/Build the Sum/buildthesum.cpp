#include <iostream>

using namespace std;

void test_case() {
    int n; cin >> n;
    long sum = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        sum += x;
    }

    cout << sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        test_case();
    }

    return 0;
}
