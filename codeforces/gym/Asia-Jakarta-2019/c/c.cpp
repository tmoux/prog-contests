#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//011001
//100110
//100110
//011001
//011001
//100110

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    vector<int> r(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
        r[i] &= 1;
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        c[i] &= 1;
    }
    vector<int> rx(n), cx(n);
    int pt = 0;
    for (int i = 0; i < n; i++) {
        rx[i] = pt;
        if (i+1 < n && r[i+1] != r[i]) {
            pt++;
        }
        //cout << i << ": " << rx[i] << '\n';
    }
    pt = 0;
    for (int i = 0; i < n; i++) {
        cx[i] = pt;
        if (i+1 < n && c[i+1] != c[i]) {
            pt++;
        }
        //cout << i << ": " << cx[i] << '\n';
    }
    while (q--) {
        int ra, ca, rb, cb; cin >> ra >> ca >> rb >> cb;
        ra--; ca--; rb--; cb--;
        cout << (rx[ra]==rx[rb]&&cx[ca]==cx[cb] ? "YES":"NO") << '\n';
    }
}

