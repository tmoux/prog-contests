#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
const int maxk = 17;
int n, q;

vector<int> adj[maxn];

int tin[maxn];
int pt = 1;
int depth[maxn];
int par[maxk][maxn];
void dfs(int i, int p) {
    tin[i] = pt++;
    depth[tin[i]] = depth[tin[p]] + 1;
    par[0][tin[i]] = tin[p];
    for (int k = 1; k < maxk; k++) {
        par[k][tin[i]] = par[k-1][par[k-1][tin[i]]];
    }
    for (int j: adj[i]) {
        dfs(j,i);
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

int comp[maxn];
int sz[maxn];
void dfs2(int i, int c) {
    comp[tin[i]] = c;
    sz[tin[i]] = adj[i].empty() ? 1 : 0;
    for (int j: adj[i]) {
        dfs2(j,c);
        sz[tin[i]] += sz[tin[j]];
    }
}

set<int> sets[maxn];
int cur_lca[maxn];

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("gangsters.in","r",stdin);
    freopen("gangsters.out","w",stdout);
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int pi; cin >> pi;
        adj[pi].push_back(i);
    }
    dfs(1,0);
    int p = 1;
    for (int j: adj[1]) {
        dfs2(j,p++);
    }
    int tot = 0, extra = 0;
    memset(cur_lca,-1,sizeof cur_lca);
    while (q--) {
        //cout << "query " << q << '\n';
        char c; int v; cin >> c >> v;
        v = tin[v];
        int com = comp[v];
        if (cur_lca[com] != -1) {
            tot--;
            extra -= sz[cur_lca[com]] - sets[com].size();
        }

        if (c == '+') {
            sets[com].insert(v);
        }
        else {
            sets[com].erase(v);
        }

        if (!sets[com].empty()) {
            int a = *sets[com].begin();
            int b = *sets[com].rbegin();
            cur_lca[com] = lca(a,b);
            tot++;
            extra += sz[cur_lca[com]] - sets[com].size();
        }
        else {
            cur_lca[com] = -1;
        }
        cout << tot << ' ' << extra << '\n';
    }
}

