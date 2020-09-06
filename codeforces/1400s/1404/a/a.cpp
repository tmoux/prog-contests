#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') a[i] = 1;
        else if (s[i] == '0') a[i] = 0;
        else a[i] = -1;
    }
    vector<set<int>> vs(k);
    for (int i = 0; i < n; i++) {
        if (a[i] >= 0) {
            vs[i%k].insert(a[i]);    
        }
    }
    bool poss = true;
    int c0 = 0, c1 = 0;
    for (int i = 0; i < k; i++) {
        if (vs[i].size() > 1) {
            poss = false;
        }
        else if (vs[i].size() == 1) {
            int id = *vs[i].begin();
            if (id == 0) {
                c0++;
            }
            else c1++;
        }
    }
    if (c0 > k/2 || c1 > k/2) poss = false;
    cout << (poss ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
