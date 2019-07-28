#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;

struct Edge
{
    int to;
    ll wt;
};

vector<Edge> adj[maxn];

bool blocked[maxn];
int sub_size[maxn];

int dfsSize(int i, int p) {
    sub_size[i] = 1;
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        sub_size[i] += dfsSize(e.to,i);
    }
    return sub_size[i];
}

int getCentroid(int i, int p, int compSize) {
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        if (sub_size[e.to] * 2 > compSize) return getCentroid(e.to,i,compSize);
    }
    return i;
}

struct Node
{
    int anc;
    map<int,ll> dist;
    map<int,int> subtree;
    map<int,multiset<ll>> mul;
    multiset<ll> ds; //multiset of max dist for subtree

    ll getd() {
        if (ds.size() == 1) return *ds.rbegin();
        return (*prev(ds.end()) + *prev(prev(ds.end())));
    }

} nodes[maxn];

void dfsDist(int i, int p, int orig, int sub, ll d) {
    nodes[orig].dist[i] = d;
    nodes[orig].subtree[i] = sub;
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        dfsDist(e.to,i,orig,sub,d+e.wt);
    }
}

multiset<ll> diams;

int decomp(int i) {
    int compSize = dfsSize(i,i);
    int centroid = getCentroid(i,i,compSize);
    blocked[centroid] = true;
    nodes[centroid].dist[centroid] = 0;
    nodes[centroid].subtree[centroid] = centroid;
    for (Edge e: adj[centroid]) {
        if (blocked[e.to]) continue;
        dfsDist(e.to,centroid,centroid,e.to,e.wt);
        int c = decomp(e.to);
        nodes[c].anc = centroid;
    }
    for (auto& p: nodes[centroid].dist) {
        int sub = nodes[centroid].subtree[p.first];
        nodes[centroid].mul[sub].insert(p.second);
    }
    for (auto& p: nodes[centroid].mul) {
        assert(!p.second.empty());
        nodes[centroid].ds.insert(*(p.second.rbegin()));
    }

    return centroid;
}

int n, q;
ll w;
vector<pair<int,int>> edges;

void eraseOne(multiset<ll>& m, ll x) {
    m.erase(m.lower_bound(x));
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    cin >> w;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        ll c; cin >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
        edges.push_back({a,b});
    }
    decomp(1);
    ll last = 0;
    while (q--) {
        int dj; cin >> dj;
        ll ej; cin >> ej;
        dj = (dj+last) % (n-1);
        ej = (ej+last) % w;
        //printf("dj = %d, ej = %d\n",dj,ej);
        int u = edges[dj].first;
        int v = edges[dj].second;
        if (!nodes[u].dist.count(v)) swap(u,v);
        //assume u is ancestor of v
    }
}

