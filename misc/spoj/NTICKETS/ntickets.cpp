#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
const int maxk = 18;
int n, q, up[maxk][maxn], maxr[maxk][maxn], depth[maxn];
vector<int> adj[maxn];
map<pair<int,int>,int> wt;

void dfs(int i, int par) {
    maxr[0][i] = wt[{i,par}];
    up[0][i] = par;
    for (int j: adj[i]) {
        if (j == par) continue;
        depth[j] = depth[i] + 1;
        dfs(j,i);
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u,v);
    for (int k = maxk - 1; k >= 0; k--) {
        int vv = up[k][v];
        if (vv != -1 && depth[u] <= depth[vv]) v = vv;
    }
    if (u == v) return u;
    for (int k = maxk - 1; k >= 0; k--) {
        int uu = up[k][u], vv = up[k][v];
        if (uu != vv) {
            u = uu;
            v = vv;
        }
    }
    return up[0][u];
}

int getMax(int u, int lc) {
    int res = 0;
    for (int k = maxk - 1; k >= 0; k--) {
        int uu = up[k][u];
        if (uu != -1 && depth[lc] <= depth[uu]) {
            res = max(res,maxr[k][u]);
            u = uu;
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    while (true) {
        cin >> n;
        if (!n) break;
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 0; i < n - 1; i++) {
            int a, b, t; cin >> a >> b >> t;
            adj[a].push_back(b);
            adj[b].push_back(a);
            wt[{a,b}] = t;
            wt[{b,a}] = t;
        }
        dfs(1,-1);
        for (int k = 1; k < maxk; k++) {
            for (int i = 1; i <= n; i++) {
                if (up[k-1][i] == -1) {
                    up[k][i] = -1;
                }
                else {
                    up[k][i] = up[k-1][up[k-1][i]];
                    maxr[k][i] = max(maxr[k-1][i],maxr[k-1][up[k-1][i]]);
                }
            }
        }
        cin >> q;
        while (q--) {
            int a, b; cin >> a >> b;
            int lc = lca(a,b);
            int ans = max(getMax(a,lc),getMax(b,lc));
            cout << ans << '\n';
        }
        cout << '\n';
    }

    return 0;
}