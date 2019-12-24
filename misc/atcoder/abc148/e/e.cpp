#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll n; cin >> n;
    if (n % 2 == 1) {
        cout << 0 << endl;
    }
    else {
        ll ans = 0;
        ll div = 10;
        while (n/div > 0) {
            ans += n/div;
            div *= 5;
        }
        cout << ans << endl;
    }
}
