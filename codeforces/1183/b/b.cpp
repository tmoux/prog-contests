#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int q; cin >> q;
    while (q--) {
        int n, k; cin >> n >> k;
        int mn = 999999999, mx = -999;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            mn = min(mn,ai);
            mx = max(mx,ai);
        }
        if (mn + k >= mx-k) {
            cout << (mn+k) << '\n';
        }
        else {
            cout << -1 << '\n';
        }
    }

}

