#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
struct Edge
{
    int from, to, wt;
    bool active = true;
};
vector<Edge> adj[maxn];
int N, M, K;

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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    memset(parent,-1,sizeof parent);
    cin >> N >> M >> K;
    vector<Edge> edges;
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        edges.push_back({a,b,c});
    }
    //find mst
    sort(edges.begin(),edges.end(),[](auto a, auto b) {
            return a.wt < b.wt;
            });
    for (Edge& e: edges) {
        if (Find(e.from) == Find(e.to)) continue;
        Union(e.from,e.to);
        adj[e.from].push_back({e.from,e.to,e.wt});
        adj[e.to].push_back({e.to,e.from,e.wt});
        //cout << e.from << ' ' << e.to << '\n';
    }
    //add extra edges
    for (int i = 0; i < K; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back({a,b,0,false});
        adj[b].push_back({b,a,0,false});
    }

}

