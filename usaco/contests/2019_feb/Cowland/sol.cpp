#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxk = 17;
int N, Q, pre[maxn], par[maxk][maxn], depth[maxn];
vector<int> adj[maxn];
map<int,int> mp;
int val[maxn];
int inn[maxn], out[maxn];
int t = 0;

void DFS(int i, int p) {
    inn[i] = ++t;
    par[0][i] = p;
    depth[i] = depth[p] + 1;
    for (int j = 1; j < maxk; j++) 
        par[j][i] = par[j-1][par[j-1][i]];
    for (int j: adj[i]) {
        if (j == p) continue;
        DFS(j,i);
    }
    out[i] = t-1;
}

void DFS2(int i, int p) {
    pre[i] = val[i] ^ pre[p];
    for (int j: adj[i]) {
        if (j == p) continue;
        DFS2(j,i);
    }
}

void refreshVal() {
    for (auto p: mp) val[p.first] = p.second;
    mp.clear();
    DFS2(1,0);
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u,v);
    for (int i = maxk - 1; i >= 0; i--) {
        int vv = par[i][v];
        if (depth[vv] >= depth[u]) v = vv;
    }
    if (u == v) return u;
    for (int i = maxk - 1; i >= 0; i--) {
        int uu = par[i][u];
        int vv = par[i][v];
        if (uu != vv) {
            u = uu;
            v = vv;
        }
    }
    return par[0][u];
}

bool inSubtree(int a, int b) {
    //if b is in subtree of a
    return inn[a] <= inn[b] && inn[b] <= out[a];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> val[i];
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    DFS(1,0);
    refreshVal();
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            //update
            int i, v; cin >> i >> v;
            mp[i] = v;
        }
        else {
            if (mp.size() > 500) refreshVal();
            int u, v; cin >> u >> v;
            int lc = lca(u,v);
            int anc = par[0][lc];
            int ans = pre[u] ^ pre[v] ^ pre[lc] ^ pre[anc];
            for (auto p: mp) {
                if (inSubtree(lc,p.first) && (inSubtree(p.first,u) || inSubtree(p.first,v))) {
                    ans ^= val[p.first] ^ p.second;
                }
            }
            cout << ans << '\n';
        }
    }
}

