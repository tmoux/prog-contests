#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            sum += ai;
        }
        sum = (sum % n == 0 ? sum/n : sum/n+1);
        cout << sum << '\n';
    }
}

