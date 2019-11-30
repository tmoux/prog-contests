#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
struct Edge
{
    int from, to;
    ll w;
};
vector<Edge> adj[maxn];
int n, m, k, q;
const ll INF = 1e18;
ll d[maxn];

//dsu stuff
int parent[maxn]; //memset to -1
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}

const int maxk = 19;
int par[maxk][maxn];
ll mx[maxk][maxn];
int depth[maxn];

void dfs(int i, int p, ll w) {
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    mx[0][i] = w;
    for (int k = 1; k < maxk; k++) {
        par[k][i] = par[k-1][par[k-1][i]];
        mx[k][i] = max(mx[k-1][i],mx[k-1][par[k-1][i]]);
    }
    for (Edge& e: adj[i]) {
        if (e.to == p) continue;
        dfs(e.to,i,e.w);
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

ll max_walk(int a, int lc) {
    ll res = 0;
    for (int k = maxk-1; k >= 0; k--) {
        int aa = par[k][a];
        if (depth[aa] >= depth[lc]) {
            res = max(res,mx[k][a]);
            a = aa;
        }
    }
    return res;
}

int main() {
    memset(parent,-1,sizeof parent);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k >> q;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({u,v,w});
        adj[v].push_back({v,u,w});
    }
    set<pair<ll,int>> setds;
    for (int i = 1; i <= n; i++) {
        d[i] = i<=k?0:INF;
        if (i <= k) {
            setds.insert({0,i});
        }
    }
    while (!setds.empty()) {
        auto p = *setds.begin();
        setds.erase(setds.begin());
        int u = p.second;
        for (Edge& e: adj[u]) {
            int v = e.to;
            ll w = e.w;
            if (d[v] > d[u] + w) {
                if (d[v] != INF) {
                    setds.erase(setds.find({d[v],v}));
                }
                d[v] = d[u] + w;
                setds.insert({d[v],v});
            }
        }
    }

    //update edges
    vector<Edge> edges;
    for (int i = 1; i <= n; i++) {
        for (Edge& e: adj[i]) {
            e.w = e.w + d[i] + d[e.to];
            if (i < e.to) {
                edges.push_back({i,e.to,e.w});
            }
        }
    }
    sort(edges.begin(),edges.end(),[](auto a, auto b) {
            return a.w < b.w;
            });
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
    for (Edge e: edges) {
        if (Find(e.from) != Find(e.to)) {
            Union(e.from,e.to);
            adj[e.from].push_back({e.from,e.to,e.w});
            adj[e.to].push_back({e.to,e.from,e.w});
        }
    }
    dfs(1,0,0);
    while (q--) {
        int a, b; cin >> a >> b;
        int lc = lca(a,b);
        ll res = max(max_walk(a,lc),max_walk(b,lc));
        cout << res << '\n';
    }
}
