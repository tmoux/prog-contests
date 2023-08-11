#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, m; cin >> n >> m;
    ll mn = max(0LL,n-2*m);
    ll mx = -1;
    for (ll i = 0; i <= n; i++) {
        if (1LL*i*(i-1)/2 >= m) {
            mx = n-i;
            break;
        }
    }
    cout << mn << ' ' << mx << '\n';
}

