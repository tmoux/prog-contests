#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<ll> a(n);
    ll gc = 0LL;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        gc = __gcd(gc,a[i]);
    }
    int ans = 0;
    for (ll i = 1; i*i <= gc; i++) {
        if (gc % i == 0) {
            if (gc/i == i) ans++;
            else ans += 2;
        }
    }
    cout << ans << '\n';
}

