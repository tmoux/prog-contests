#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxk = 17;
int n, m, q;
vector<int> adj[maxn];
int jmp[maxk][maxn];
bool vis[maxn];
int depth[maxn];
int par[maxk][maxn];
void dfs(int i, int p) {
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) 
        par[k][i] = par[k-1][par[k-1][i]];
    vis[i] = true;

    jmp[0][i] = p;
    for (int j: adj[i]) if (vis[j]) {
        if (depth[j] < depth[jmp[0][i]])
            jmp[0][i] = j;
    }
    for (int k = 1; k < maxk; k++) {
        jmp[k][i] = jmp[k-1][jmp[k-1][i]];
    }

    for (int j: adj[i]) if (!vis[j]) {
        dfs(j,i);
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);    
    for (int k = maxk-1; k >= 0; k--) {
        int bb = par[k][b];
        if (depth[bb] >= depth[a]) b = bb;
    }
    if (a == b) return a;
    for (int k = maxk-1; k >= 0; k--) {
        int aa = par[k][a];
        int bb = par[k][b];
        if (aa != bb) {
            a = aa;
            b = bb;
        }
    }
    return par[0][a];
}

int dist(int a, int lc) {
    int res = 0;
    for (int k = maxk-1; k >= 0; k--) {
        int aa = jmp[k][a];
        if (depth[aa] >= depth[lc]) {
            a = aa;
            res += 1<<k;
        }
    }
    if (depth[a] > depth[lc]) res++;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vis[0] = true;
    dfs(1,0);
    while (q--) {
        int a, b; cin >> a >> b;
        int lc = lca(a,b);
        int ans = dist(a,lc) + dist(b,lc);
        cout << ans << '\n';
    }
}
