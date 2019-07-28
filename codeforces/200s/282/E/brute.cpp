#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<ll> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] ^= a[i-1];
    }
    ll res = a[n];
    for (int l = 0; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            res = max(res,a[n]^a[r]^a[l]);
        }
    }
    cout << res << '\n';
}

