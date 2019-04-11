#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n+1);
    vector<int> cap(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cap[i] = a[i];
    }
    int q; cin >> q;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int p, x; cin >> p >> x;
            for (; p <= n; p++) {
                int take = min(a[p],x);
                a[p] -= take;
                x -= take;
                if (x == 0) break;
            }
        }
        else {
            int k; cin >> k;
            cout << (cap[k]-a[k]) << '\n';
        }
    }

}

