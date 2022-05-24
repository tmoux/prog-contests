#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    vector<int> a(n+1,0);
    while (q--) {
        int t; cin >> t;
        int l, r; cin >> l >> r;
        if (t == 1) {
            ll res = 0;
            for (int i = l; i <= r; i++) res += a[i];
            cout << res << '\n';
        }
        else {
            int x; cin >> x;
            for (int i = l; i <= r; i++) a[i] = x;
        }
    }

    return 0;
}

