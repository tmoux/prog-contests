#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n;
vector<int> adj[maxn];
int d[maxn][maxn];

int depth[maxn];
vector<pair<int,int>> edges;
int par[13][maxn];
void dfs(int i, int p) {
    par[0][i] = p;
    depth[i] = depth[p] + 1;
    for (int k = 1; k < 13; k++) {
        par[k][i] = par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);
    for (int k = 12; k >= 0; k--) {
        int bb = par[k][b];
        if (depth[bb] >= depth[a]) b = bb;
    }
    if (a == b) return a;
    for (int k = 12; k >= 0; k--) {
        int aa = par[k][a];
        int bb = par[k][b];
        if (aa != bb) {
            a = aa;
            b = bb;
        }
    }
    return par[0][a];
}

void upd(int i, int lc, int g) {
    while (i != lc) {
        d[i][par[0][i]] = max(d[i][par[0][i]],g);
        d[par[0][i]][i] = max(d[par[0][i]][i],g);
        i = par[0][i];
    }
}

int check(int i, int lc) {
    return i == lc ? 1000000 : min(d[i][par[0][i]],check(par[0][i],lc));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        edges.push_back({a,b});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,0);
    int m; cin >> m;
    vector<pair<pair<int,int>,int>> v;
    for (int i = 0; i < m; i++) {
        int a, b, g; cin >> a >> b >> g;
        v.push_back({{a,b},g});
    }
    sort(v.begin(),v.end(),[](auto a, auto b) {
            return a.second < b.second;
            });
    for (auto p: v) {
        int a = p.first.first;
        int b = p.first.second;
        int lc = lca(a,b);
        upd(a,lc,p.second);
        upd(b,lc,p.second);
    }
    for (int i = 1; i <= n; i++) {
        for (int j: adj[i]) {
            if (d[i][j] == 0) d[i][j] = 1000000;
        }
    }
    for (auto p: v) {
        int a = p.first.first;
        int b = p.first.second;
        int lc = lca(a,b);
        int mn = check(a,lc);
        mn = min(mn,check(b,lc));
        if (mn != p.second) {
            cout << -1 << '\n';
            return 0;
        }
    }
    for (auto p: edges) {
        cout << d[p.first][p.second] << ' ';
    }
    cout << '\n';
}

