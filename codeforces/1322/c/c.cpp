#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            --u; --v;
            adj[v].push_back(u);
        }
        map<vector<int>,ll> mp;
        for (int i = 0; i < n; i++) {
            sort(adj[i].begin(),adj[i].end());
            mp[adj[i]] += a[i];
        }
        ll res = 0;
        for (auto p: mp) {
            if (p.first.empty()) continue;
            res = __gcd(res,p.second);
        }
        cout << res << '\n';
    }
}
