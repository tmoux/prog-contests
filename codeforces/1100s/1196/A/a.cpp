#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        vector<ll> a(3);
        for (int i = 0; i < 3; i++) {
            cin >> a[i];
        }
        sort(a.begin(),a.end());
        ll a1 = a[0];
        ll a2 = a[1];
        ll even = min(a2-a1,a[2]);
        a1 += even;
        a[2] -= even;
        if (a[2] > 0) {
            a1 += a[2]/2;
            a[2] -= a[2]/2;
            a2 += a[2];
        }
        cout << min(a1,a2) << '\n';
    }

}

