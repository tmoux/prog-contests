#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7, maxn = 1e5+5;
int n;
vector<int> adj[maxn];
int sz[maxn];
vector<ll> cnt;

void dfs(int i, int p) {
    sz[i] = 1;
    for (int j: adj[i]) if (j != p) {
        dfs(j,i);
        sz[i] += sz[j];
    }
    if (i != p) {
        cnt.push_back(1LL*(sz[i])*(n-(sz[i])));
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        cnt.clear();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (int i = 0; i < n-1; i++) {
            int u, v; cin >> u >> v;
            --u; --v;
            //cout << u << ' ' << v << endl;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0,0);
        sort(cnt.begin(),cnt.end());
        for (auto& i: cnt) i %= M;
        int m; cin >> m;
        vector<ll> ps(m);
        for (int i = 0; i < m; i++) {
            cin >> ps[i];
        }
        while (ps.size() < n-1) ps.push_back(1LL);
        sort(ps.begin(),ps.end());
        while (ps.size() > n-1) {
            ll z = ps.back();
            ps.pop_back();
            ll y = ps.back();
            ps.pop_back();
            ps.push_back((z*y)%M);
        }
        ll ans = 0;
        for (int i = 0; i < n-1; i++) {
            ll add = (1LL*cnt[i]*ps[i]) % M;
            ans = (ans + add) % M;
            //cout << cnt[i] << ' ' << ps[i] << endl;
        }
        cout << ans << '\n';
    }
}
