#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
void madd(int& a, int b) {
    a = (a+b) % M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
const int maxn = 2e5+5, maxk = 19;
int n, m;
int dist[maxk*maxn];

int cv(int i, int j) {
    return i+j*n;
}

struct Edge {
    int to, wt;
};
vector<Edge> adj[maxk*maxn];

const int INF = 2e9;
vector<int> dijkstra(int source) {
    vector<int> dist(maxk*maxn,INF);
    dist[source] = 0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0LL,source});
    while (!pq.empty()) {
        int u = pq.top().second; 
        int d = pq.top().first;
        pq.pop();
        if (d > dist[u]) continue; 
        for (Edge& e: adj[u]) {
            int v = e.to;
            int weight = e.wt;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v],v});
            }
        }
    }
    return dist;
}

pair<int,int> operator+(pair<int,int> a, pair<int,int> b) {
    return {a.first+b.first,a.second+b.second};
}
vector<pair<int,pair<int,int>>> adj2[maxn*2];
vector<pair<int,int>> dijkstra2(int source) {
    vector<pair<int,int>> dist(maxn*2,{INF,INF});
    dist[source] = {0,0};
    priority_queue<pair<pair<int,int>,int>,vector<pair<pair<int,int>,int>>,greater<pair<pair<int,int>,int>>> pq;
    pq.push({{0,0},source});
    while (!pq.empty()) {
        int u = pq.top().second; 
        auto d = pq.top().first;
        pq.pop();
        if (d > dist[u]) continue; 
        for (auto& e: adj2[u]) {
            int v = e.first;
            auto weight = e.second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v],v});
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        --u; --v;
        for (int j = 0; j < maxk; j += 2) {
            adj[cv(u,j)].push_back({cv(v,j),1});
        }
        for (int j = 1; j < maxk; j += 2) {
            adj[cv(v,j)].push_back({cv(u,j),1});
        }

        adj2[u].push_back({v,{0,1}});
        adj2[v+n].push_back({u+n,{0,1}});
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 1 < maxk; j++) {
            adj[cv(i,j)].push_back({cv(i,j+1),1<<j});
        }
        adj2[i].push_back({i+n,{1,0}});
        adj2[i+n].push_back({i,{1,0}});
    }
    auto d = dijkstra(cv(0,0));
    int ans = INF;
    for (int j = 0; j < maxk; j++) {
        ans = min(ans,d[cv(n-1,j)]);
    }
    if (ans < INF) {
        cout << ans << '\n';
    }
    else {
        auto d = dijkstra2(0);
        auto res = min(d[n-1],d[n-1+n]);
        int ans = modexp(2,res.first);
        madd(ans,M-1);
        madd(ans,res.second);
        cout << ans << '\n';
    }
}
