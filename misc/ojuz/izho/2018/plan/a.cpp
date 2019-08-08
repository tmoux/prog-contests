#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m, k;
struct Edge
{
    int from, to, wt;
};

vector<Edge> adj[maxn];

int d[maxn]; //min distance from black nodes

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

vector<Edge> mst[maxn];

const int maxk = 18;
int depth[maxn];
int par[maxk][maxn];
int mn[maxk][maxn];
void root(int i, int p) {
    for (Edge& e: mst[i]) {
        if (e.to == p) continue;
        depth[e.to] = depth[i] + 1;
        par[0][e.to] = i;
        mn[0][e.to] = e.wt;
        for (int k = 1; k < maxk; k++) {
            par[k][e.to] = par[k-1][par[k-1][e.to]];
            mn[k][e.to] = min(mn[k-1][e.to],mn[k-1][par[k-1][e.to]]);
        }
        root(e.to,i);
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

int walk(int a, int lc) { //returns min on path a -> lc
    int res = 2e9+9;
    for (int k = maxk - 1; k >= 0; k--) {
        int aa = par[k][a];
        if (depth[aa] >= depth[lc]) {
            res = min(res,mn[k][a]);
            a = aa;
        }
    }
    return res;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    cin >> n >> m;
    for (int k = 0; k < maxk; k++) {
        for (int i = 0; i <= n; i++) {
            mn[k][i] = 2e9+9;
        }
    }
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int a, b, w; cin >> a >> b >> w;
        adj[a].push_back({a,b,w});
        adj[b].push_back({b,a,w});
        edges.push_back({a,b,w});
    }
    cin >> k;
    queue<int> bad;
    for (int i = 1; i <= n; i++) {
        d[i] = 2e9+9;
    }
    for (int i = 0; i < k; i++) {
        int ai; cin >> ai;
        bad.push(ai);
        d[ai] = 0;
    }
    while (!bad.empty()) {
        int f = bad.front(); bad.pop();
        //cout << f << ": " << d[f] << '\n';
        for (Edge& e: adj[f]) {
            if (d[e.to] > d[f] + e.wt) {
                d[e.to] = d[f] + e.wt;
                bad.push(e.to);
            }
        }
    }
    for (Edge& e: edges) {
        e.wt = min(d[e.from],d[e.to]);
        //printf("%d -> %d: %d\n",e.from,e.to,e.wt);
    }
    sort(edges.begin(),edges.end(),[](auto a, auto b) {
            return a.wt > b.wt;
            });
    for (Edge& e: edges) {
        if (Find(e.from) == Find(e.to)) {
            continue;
        }
        else {
            Union(e.from,e.to);
            mst[e.from].push_back({e.from,e.to,e.wt});
            mst[e.to].push_back({e.to,e.from,e.wt});
            //printf("%d -> %d: %d\n",e.from,e.to,e.wt);
        }
    }
    root(1,1);
    int Q; cin >> Q;
    while (Q--) {
        int a, b; cin >> a >> b;
        int lc = lca(a,b);
        int ans = min(walk(a,lc),walk(b,lc));
        assert(ans < 2e9);
        //printf("lca = %d, w1 = %d, w2 = %d\n", lc,walk(a,lc),walk(b,lc));
        cout << ans << '\n';
    }
}
