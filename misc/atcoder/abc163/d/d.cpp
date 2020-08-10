#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    ll ans = 0;
    for (ll i = k; i <= n+1; i++) {
        ll mn = i*(i-1)/2;
        ll mx = (n-i+1+n)*i/2;
        ans += (mx-mn+1);
        ans %= M;
        //cout << i << ": " << mn << ' ' << mx << '\n';
    }
    cout << ans << '\n';
}
