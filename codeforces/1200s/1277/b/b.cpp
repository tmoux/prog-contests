#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int d = 0;
        int c = n;
        while (c > 0) {
            d++;
            c /= 10;
        }
        int ans = 9*(d-1);
        for (int i = 1; i <= 9; i++) {
            ll tr = 0;
            ll mult = 1;
            for (int k = 0; k < d; k++) {
                tr += i*mult;
                mult *= 10;
            }
            if (tr <= (ll)n) {
                ans++;
            }
            else break;
        }
        cout << ans << '\n';
    }
}

