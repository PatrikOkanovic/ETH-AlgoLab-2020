#include <iostream>

using namespace std;

void test_case() {
    int n; cin >> n;
    int even = 0, odd = 0, sum = 0;
    for (int i = 0; i < n; i++) {
        int xi; cin >> xi;
        sum += xi;
        if (sum % 2 == 0) even++;
        else odd ++;
    }

    cout << even * (even - 1) / 2 + odd * (odd - 1) / 2 + even << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        test_case();
    }

    return 0;
}
