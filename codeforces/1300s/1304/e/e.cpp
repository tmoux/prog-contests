#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxk = 17;
vector<int> adj[maxn];
int depth[maxn];
int par[maxk][maxn];
int n, q;

void dfs(int i, int p) {
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
        par[k][i] = par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        depth[j] = depth[i] + 1;
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

int dist(int a, int b) {
    return depth[a] + depth[b] - 2*depth[lca(a,b)];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    cin >> q;
    while (q--) {
        int x, y, a, b, k; cin >> x >> y >> a >> b >> k;
        bool poss = false;
        int par = k % 2;
        if (dist(a,b) <= k && dist(a,b) % 2 == par) poss = true;
        if (dist(a,x)+1+dist(y,b) <= k && (dist(a,x)+1+dist(y,b)) % 2 == par) poss = true;
        if (dist(a,y)+1+dist(x,b) <= k && (dist(a,y)+1+dist(x,b)) % 2 == par) poss = true;
        cout << (poss ? "YES" : "NO") << endl;
    }
}

