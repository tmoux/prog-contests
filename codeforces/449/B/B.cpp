#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
const ll INF = 1e18;
int n, m, k;
struct Edge { int to, w; };
vector<Edge> adj[maxn];
vector<int> train[maxn];
int ans = 0;

vector<ll> dijkstra() {
    set<pair<ll,int>> setds;
    vector<ll> dist(n+1,INF);
    setds.insert({0,1});
    dist[1] = 0;
    while (!setds.empty()) {
        auto tmp = *(setds.begin());
        setds.erase(setds.begin());
        int u = tmp.second;
        for (Edge& e: adj[u]) {
            int v = e.to;
            ll weight = e.w;
            if (dist[v] > dist[u] + weight) {
                if (dist[v] != INF) {
                    auto it = setds.find({dist[v],v});
                    if (it != setds.end()) setds.erase(it);
                    //setds.erase(setds.find({dist[v],v}));
                }
                dist[v] = dist[u] + weight;
                setds.insert({dist[v],v});
            }
        }
    }
    return dist;
}

int indegree[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    for (int i = 0; i < k; i++) {
        int s, y; cin >> s >> y;
        train[s].push_back(y);
    }
    for (int i = 1; i <= n; i++) sort(train[i].begin(),train[i].end());

    for (int i = 1; i <= n; i++) {
        if (train[i].empty()) continue;
        ans += train[i].size() - 1;
        adj[1].push_back({i,train[i].front()});
    }

    vector<ll> dist = dijkstra();
    for (int u = 1; u <= n; u++) {
        for (Edge& e: adj[u]) {
            int v = e.to;
            ll w = e.w;
            if (dist[u] + w == dist[v]) {
                indegree[v]++;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (train[i].empty()) continue;
        ll w = train[i].front();
        if (w > dist[i]) ans++;
        else if (indegree[i] > 1) ans++;
    }
    cout << ans << '\n';
    

        
    return 0;
}

