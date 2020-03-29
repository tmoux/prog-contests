#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
const int maxn = 250005, maxk = 18;
int n, q;
int a[maxn];
vector<int> adj[maxn];

pair<int,int> merge(pair<int,int> a, pair<int,int> b) {
    if (a.first == -1) return b;
    if (b.first == -1) return a;
    if (a.first == b.first) return {a.first,a.second+b.second};
    if (a.second >= b.second) return {a.first,a.second-b.second};
    return {b.first,b.second-a.second};
}

vector<int> v[maxn], rev[maxn];
int tin[maxn];
int t = 0;
//lca
int par[maxk][maxn];
int depth[maxn];
pair<int,int> path[maxk][maxn];
void dfs(int i, int p) {
    depth[i] = depth[p]+1;
    par[0][i] = p;
    path[0][i] = {a[i],1};
    for (int k = 1; k < maxk; k++) {
        par[k][i] = par[k-1][par[k-1][i]];
        path[k][i] = merge(path[k-1][i],path[k-1][par[k-1][i]]);
    }
    tin[i] = t;
    v[a[i]].push_back(t++);
    for (int j: adj[i]) if (j != p) {
        dfs(j,i);
    }
    rev[a[i]].push_back(t++);
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);
    for (int k = maxk-1; k >= 0; k--) {
        int bb = par[k][b];
        if (depth[bb] >= depth[a]) {
            b = bb;
        }
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

inline int countPath(int lc, int a, int x) {
    return distance(lower_bound(all(v[x]),tin[lc]),upper_bound(all(v[x]),tin[a])) - distance(lower_bound(all(rev[x]),tin[lc]),upper_bound(all(rev[x]),tin[a]));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,0);
    while (q--) {
        int u, v; cin >> u >> v;
        int lc = lca(u,v);
        int len = depth[u] + depth[v] - 2*depth[lc] + 1;
        int target = len/2+1;
        pair<int,int> m = {-1,-1};
        int uu = u;
        for (int k = maxk-1; k >= 0; k--) {
            if (depth[par[k][uu]] >= depth[lc]) {
                m = merge(m,path[k][uu]);
                uu = par[k][uu];
            }
        }
        int vv = v;
        for (int k = maxk-1; k >= 0; k--) {
            if (depth[par[k][vv]] >= depth[lc]) {
                m = merge(m,path[k][vv]);
                vv = par[k][vv];
            }
        }
        m = merge(m,{a[lc],1});
        int x = m.first;
        int cnt = countPath(lc,u,x) + countPath(lc,v,x);
        if (a[lc] == x) --cnt;
        if (cnt >= target) {
            cout << x << '\n';
        }
        else {
            cout << -1 << '\n';
        }
    }
}
