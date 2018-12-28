#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, q, a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> q;
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        if (t == 1) {
            //query
            ll res = 0;
            for (int i = l; i <= r; i++) {
                res += a[i];
            }
            cout << res << '\n';
        }
        else {
            //update
            int x; cin >> x;
            for (int i = l; i <= r; i++) {
                a[i] ^= x;
            }
        }
    }

    return 0;
}

