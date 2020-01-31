#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m, a[maxn];
struct Edge
{
    int to, from, wt;
};

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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    cin >> n >> m;
    vector<Edge> edges;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        edges.push_back({u,v,min(a[u],a[v])});
    }
    sort(edges.begin(),edges.end(),[](auto a, auto b) {
        return a.wt > b.wt;        
            });
    ll tot = 0;
    for (auto e: edges) {
        if (Find(e.to) == Find(e.from)) continue;
        int a = -parent[Find(e.to)];
        int b = -parent[Find(e.from)];
        tot += 2LL*e.wt*a*b;
        Union(e.to,e.from);
        //printf("%d %d, wt = %d: %d\n",e.to,e.from,e.wt,tot);
    }
    cout << fixed << setprecision(10) << ((double)tot/n/(n-1)) << endl;
}

