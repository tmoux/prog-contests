#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n; cin >> n;
    ll ans = n-1;
    for (ll i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            ll j = n/i;
            ll tr = i + j - 2;
            ans = min(ans,tr);
        }
    }
    cout << ans << '\n';
}

