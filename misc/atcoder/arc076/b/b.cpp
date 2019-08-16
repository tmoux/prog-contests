#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int N;
int x[maxn], y[maxn];
    
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

struct Point
{
    int x, y, id;
};

struct Edge
{
    int u, v, wt;
};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    memset(parent,-1,sizeof parent);
    vector<Point> xs, ys;
    for (int i = 0; i < N; i++) {
        cin >> x[i] >> y[i];
        xs.push_back({x[i],y[i],i});
        ys.push_back({x[i],y[i],i});
    }
    vector<Edge> edges;
    sort(xs.begin(),xs.end(),[](auto a, auto b) {
            return a.x < b.x; });
    sort(ys.begin(),ys.end(),[](auto a, auto b) {
            return a.y < b.y; });
    for (int i = 0; i < N-1; i++) {
        edges.push_back({xs[i].id,xs[i+1].id,xs[i+1].x-xs[i].x});
    }
    for (int i = 0; i < N-1; i++) {
        edges.push_back({ys[i].id,ys[i+1].id,ys[i+1].y-ys[i].y});
    }
    sort(edges.begin(),edges.end(),[](auto a, auto b) { return a.wt < b.wt; });
    ll ans = 0;
    for (Edge e: edges) {
        if (Find(e.u) == Find(e.v)) continue;
        else {
            ans += e.wt;
            Union(e.u,e.v);
        }
    }
    cout << ans << '\n';
}

