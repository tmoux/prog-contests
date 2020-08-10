#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, maxk = 18;
int N, Q;
vector<int> adj[maxn];
int A[maxn];
int depth[maxn];
int par[maxk][maxn];

void dfs(int i, int p, int d) {
    par[0][i] = p;
    depth[i] = d;
    for (int k = 1; k < maxk; k++) {
        par[k][i] = par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) if (j != p) {
        dfs(j,i,d+1);
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

void solve() {
    cin >> N >> Q;
    for (int i = 0; i <= N; i++) {
        A[i] = 0;
        adj[i].clear();
        depth[i] = 0;
        for (int k = 0; k < maxk; k++) {
            par[k][i] = 0;
        }
    }
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0,1);
    while (Q--) {
        int a, b; cin >> a >> b;
        int lc = lca(a,b);
        int dist = depth[a] + depth[b] - 2*depth[lc] + 1;
        if (dist > 100) {
            cout << 0 << '\n';
        }
        else {
            vector<int> v = {A[lc]};
            int x = a;
            while (x != lc) {
                v.push_back(A[x]);
                x = par[0][x];
            }
            x = b;
            while (x != lc) {
                v.push_back(A[x]);
                x = par[0][x];
            }
            sort(v.begin(),v.end());
            int ans = 105;
            for (int i = 0; i < v.size()-1; i++) {
                ans = min(ans,v[i+1]-v[i]);
            }
            cout << ans << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
