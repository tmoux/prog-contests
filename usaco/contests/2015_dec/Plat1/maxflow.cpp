#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 50005, maxk = 17;
int n, par[maxk][maxn], dp[maxn];
vector<int> adj[maxn];
int depth[maxn];

void dfs(int i, int p, int d) {
    par[0][i] = p;
    depth[i] = d;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i,d+1);
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u,v);
    for (int k = maxk - 1; k >= 0; k--) {
        if (par[k][v] != 0 && depth[par[k][v]] >= depth[u]) {
            v = par[k][v];
        }
    }
    if (u == v) return u;
    for (int k = maxk - 1; k >= 0; k--) {
        int uu = par[k][u], vv = par[k][v];
        if (uu != vv) {
            u = uu;
            v = vv;
        }
    }
    return par[0][u];
}

int ans = 0;
int dfs2(int i, int p) {
    for (int j: adj[i]) {
        if (j == p) continue;
        dp[i] += dfs2(j,i);    
    }
    ans = max(ans,dp[i]);
    return dp[i];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("maxflow.in","r",stdin);
    //freopen("maxflow.out","w",stdout);
    int k;
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0,0);
    for (int k = 1; k < maxk; k++) {
        for (int i = 1; i <= n; i++) {
            par[k][i] = par[k-1][par[k-1][i]];
        }
    }
    while (k--) {
        int u, v; cin >> u >> v;
        int lc = lca(u,v);
        dp[u]++;
        dp[v]++;
        dp[lc]--;
        dp[par[0][lc]]--;
    }
    dfs2(1,1);
    cout << ans << '\n';

    return 0;
}

