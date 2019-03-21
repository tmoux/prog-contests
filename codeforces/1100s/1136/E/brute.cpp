#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<ll> a(n+10);
    vector<ll> k(n+10);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n - 1; i++) cin >> k[i];
    int q; cin >> q;
    while (q--) {
        char c; cin >> c;
        if (c == 's') {
            int l, r; cin >> l >> r;
            ll sum = 0;
            for (int i = l; i <= r; i++) {
                sum += a[i];
            }
            cout << sum << '\n';
        }
        else {
            int i, x; cin >> i >> x;
            a[i] += x;
            for (int j = i + 1; j <= n; j++) {
                a[j] = max(a[j],a[j-1]+k[j-1]);
            }
        }
    }
}

