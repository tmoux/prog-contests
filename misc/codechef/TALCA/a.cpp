#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
const int maxk = 18;
int par[maxk][maxn];
int depth[maxn];
int n;
vector<int> adj[maxn];

void root(int i, int p) {
    for (int j: adj[i]) {
        if (j == p) continue;
        depth[j] = depth[i] + 1;
        par[0][j] = i;
        for (int k = 1; k < maxk; k++) {
            par[k][j] = par[k-1][par[k-1][j]];
        }
        root(j,i);
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);
    for (int k = maxk - 1; k >= 0; k--) {
        int bb = par[k][b];
        if (bb != 0 && depth[bb] >= depth[a])
            b = bb;
    }
    if (a == b) return a;
    for (int k = maxk - 1; k >= 0; k--) {
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

pair<int,int> solve(int u, int lc, int r) {
    for (int k = maxk-1; k >= 0; k--) {
        int a = par[k][u], b = par[0][a];
        if (b != 0 && depth[b] < depth[lc]) continue;
        if (dist(b,r) < dist(a,r)) {
            u = b;
        }
    }
    if (par[0][u] != 0 && depth[par[0][u]] >= depth[lc] && dist(par[0][u],r) < dist(u,r)) u = par[0][u];
    return {dist(u,r),u};
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    root(1,0);
    int q; cin >> q;
    while (q--) {
        int r, u, v; cin >> r >> u >> v;
        int lc = lca(u,v);
        auto s1 = solve(u,lc,r);
        auto s2 = solve(v,lc,r);
        cout << (s1.first < s2.first ? s1.second : s2.second) << '\n';
        /*
        cout << u << ": " << s1.first << ' ' << s1.second << '\n';
        cout << v << ": " << s2.first << ' ' << s2.second << '\n';
        */
    }
}

