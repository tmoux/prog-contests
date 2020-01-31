#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, a[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] = a[i] % 2 == 1 ? 0 : 1;
            a[i] += a[i-1];
        }
        int q; cin >> q;
        while (q--) {
            int l, r; cin >> l >> r;
            int num = a[r]-a[l-1];
            cout << (num > 0 ? "EVEN" : "ODD") << '\n';
        }
    }
}

