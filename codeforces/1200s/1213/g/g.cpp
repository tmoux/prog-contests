#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;
struct Edge
{
    int u, v, wt;
};
vector<Edge> adj[maxn];

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

ll ans[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    cin >> n >> m;
    vector<Edge> edges;
    for (int i = 0; i < n-1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
        edges.push_back({u,v,w});
    }
    sort(edges.begin(),edges.end(),[](auto a, auto b) {
        return a.wt < b.wt;
            });
    for (Edge& e: edges) {
        int u = e.u;
        int v = e.v;
        int c1 = -parent[Find(u)];
        int c2 = -parent[Find(v)];
        ans[e.wt] += 1LL*c1*c2;
        //cout << e.wt << ": " << ans[e.wt] << '\n';
        Union(u,v);
    }
    for (int i = 1; i <= 200000; i++) {
        ans[i] += ans[i-1];
    }
    while (m--) {
        int q; cin >> q;
        cout << ans[q] << ' ';
    }
    cout << '\n';
}

