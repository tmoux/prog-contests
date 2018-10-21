#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
const ll INF = 1e18;
int n, m, k;
struct Edge { int to, w; bool isTrain; };
vector<Edge> adj[maxn];
vector<int> train[maxn];
bool used[maxn];
int ans = 0;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v,w,0});
        adj[v].push_back({u,w,0});
    }
    for (int i = 0; i < k; i++) {
        int s, y; cin >> s >> y;
        train[s].push_back(y);
        adj[1].push_back({s,y,1});
        adj[s].push_back({1,y,1});
    }
    for (int i = 1; i <= n; i++) sort(train[i].begin(),train[i].end());
    for (int i = 1; i <= n; i++) {
        if (train[i].empty()) continue;
        ans += train[i].size() - 1;
    }

    //dijkstra
    set<pair<ll,int>,int>> setds;
    vector<ll> dist(n+1,INF);
    setds.insert({0,1});
    dist[1] = 0;
    while (!setds.empty()) {
        auto tmp = *(setds.begin());
        setds.erase(setds.begin());
        int u = tmp.second;
        if (!train[u].empty()) {
            int tr = *train[u].begin();
            if (dist[u] <= tr) {
                if (!used[u]) ans++;
                used[u] = true;
            }
            else {
                dist[u] = tr;
            }
        }
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
    cout << ans << '\n';
    



        
    return 0;
}

