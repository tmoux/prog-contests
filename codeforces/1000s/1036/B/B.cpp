#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(ll i, ll j, ll k) {
    ll n = max(i,j);
    if (n > k) {
        cout << -1 << '\n';
        return;
    }
    if ((i+j) % 2 == 1) {
        k--;
        n--;
    }
    else if ((n+k) % 2 == 1) {
        k -= 2;
    }

    cout << k << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        ll i, j, k; cin >> i >> j >> k;
        solve(i,j,k);
    }

    return 0;
}

