#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxk = 17;
int n;
vector<int> adj[maxn];
int depth[maxn];
int par[maxk][maxn];
int sub_size[maxn];

void dfs(int i, int p) {
    par[0][i] = p;
    depth[i] = i==1?0:depth[p] + 1;
    for (int k = 1; k < maxk; k++) {
        par[k][i] = par[k-1][par[k-1][i]];
    }
    sub_size[i] = 1;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
        sub_size[i] += sub_size[j];
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

int anc(int u, int t_depth) {
    for (int k = maxk-1; k >= 0; k--) {
        int nc = par[k][u];
        if (depth[nc] > t_depth) {
            u = nc;
        }
    }
    return u;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        if (u == v) {
            cout << n << endl;
            continue;
        }
        int d = dist(u,v);
        if (d&1) {
            cout << 0 << endl;
        }
        else {
            int lc = lca(u,v);
            int ans = n;
            if (depth[u]-d/2 > depth[lc]) {
                int t_depth = depth[u] - d/2;
                int a = anc(u,t_depth);
                ans -= sub_size[a];
                ans -= n-sub_size[par[0][a]];
            }
            else if (depth[v]-d/2 > depth[lc]) {
                int t_depth = depth[v] - d/2;
                int a = anc(v,t_depth);
                ans -= sub_size[a];
                ans -= n-sub_size[par[0][a]];
            }
            else {
                int t_depth = depth[lc];
                int a = anc(u,t_depth);
                ans -= sub_size[a];
                a = anc(v,t_depth);
                ans -= sub_size[a];
            }
            cout << ans << endl;
        }
    }
}

