#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxk = 17;
const int mx = 10;
int n, m, q;
vector<int> adj[maxn];
int par[maxk][maxn];
vector<int> mins[maxk][maxn];
int depth[maxn];

vector<int> merge(const vector<int>& a, const vector<int>& b) {
    vector<int> ret;
    int i = 0, j = 0;
    while ((i < a.size() || j < b.size()) && ret.size() < mx) {
        if (j == b.size()) {
            ret.push_back(a[i]);
            i++;
        }
        else if (i == a.size()) {
            ret.push_back(b[j]);
            j++;
        }
        else if (a[i] < b[j]) {
            ret.push_back(a[i]);
            i++;
        }
        else {
            ret.push_back(b[j]);
            j++;
        }
    }
    return ret;
}

void dfs(int i, int p) {
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
        par[k][i] = par[k-1][par[k-1][i]];
        mins[k][i] = merge(mins[k-1][i],mins[k-1][par[k-1][i]]);
        /*
        if (k < 4) {
            cout << i << ' ' << k << ":\n";
            for (int j: mins[k][i]) {
                cout << j << ' ';
            }
            cout << '\n';
        }
        */
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
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
        int aa = par[k][a], bb = par[k][b];
        if (aa != bb) {
            a = aa;
            b = bb;
        }
    }
    return par[0][a];
}

vector<int> walk(int i, int lc) {
    vector<int> ret;
    for (int k = maxk-1; k >= 0; k--) {
        int ii = par[k][i];
        if (depth[ii] >= depth[lc]) {
            ret = merge(ret,mins[k][i]);
            i = ii;
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> q;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= m; i++) {
        int ci; cin >> ci;
        mins[0][ci].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        sort(mins[0][i].begin(),mins[0][i].end());
        while (mins[0][i].size() > mx) {
            mins[0][i].pop_back();
        }
    }
    dfs(1,0);
    while (q--) {
        int v, u, a; cin >> v >> u >> a;
        int lc = lca(v,u);
        vector<int> ret;
        if (u == v) {
            ret = mins[0][lc];
        }
        else {
            ret = walk(v,lc);
            ret = merge(ret,walk(u,lc));
            ret = merge(ret,mins[0][lc]);
        }
        int k = min((int)ret.size(),a);
        cout << k << ' ';
        for (int i = 0; i < k; i++) {
            cout << ret[i] << ' ';
        }
        cout << '\n';
    }
}

