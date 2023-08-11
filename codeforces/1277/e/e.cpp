#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m, a, b;
vector<int> adj[maxn];
bool vis[maxn];

int ca = 0, cb = 0;

void dfs(int i, int avoid) {
    vis[i] = true;
    if (avoid == b) ca++;
    else cb++;
    for (int j: adj[i]) {
        if (j == avoid || vis[j]) continue;
        dfs(j,avoid);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m >> a >> b;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            ca = cb = 0;
        }
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 1; i <= n; i++) {
            vis[i] = false;
        }
        dfs(a,b);    
        for (int i = 1; i <= n; i++) {
            vis[i] = false;
        }
        dfs(b,a);
        ll ans = 1LL*(n-1-ca)*(n-1-cb);
        cout << ans << '\n';
    }
}

