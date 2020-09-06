#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, X; cin >> n >> X;
    vector<int> a(2000005,0);
    for (int i = 0; i < n; i++) {
        int ai; cin >> ai;
        ++a[ai];
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) {
        int bi = b[i];
        if (a[bi]) --a[bi];
        else if (a[bi^X]) --a[bi^X];
        else {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
