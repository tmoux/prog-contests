#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5;
const ll INF = 1e18;
int n, m, k;
struct Edge { int to; ll w; };
vector<Edge> adj[maxn];
map<pair<int,int>,int> mp;

vector<int> Dijkstra() {
    set<pair<ll,int>> setds;
    vector<ll> dist(n+1,INF);
    vector<int> parent(n+1);
    setds.insert({0,1});
    dist[1] = 0;
    while (!setds.empty()) {
        auto tmp = *setds.begin();
        setds.erase(setds.begin());
        int u = tmp.second;
        for (Edge& e: adj[u]) {
            int v = e.to;
            ll weight = e.w;
            if (dist[u] + weight < dist[v]) {
                if (dist[v] != INF) {
                    setds.erase(setds.find({dist[v],v}));    
                }
                dist[v] = dist[u] + weight;
                parent[v] = u;
                setds.insert({dist[v],v});
            }
        }
    }
    return parent;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int x, y, w; cin >> x >> y >> w;
        pair<int,int> p1 = {x,y}, p2 = {y,x};
        mp[p1] = i+1;
        mp[p2] = i+1;
        adj[x].push_back({y,w});
        adj[y].push_back({x,w});
    }
    vector<int> parent = Dijkstra();
    vector<int> indegree(n+1);
    for (int i = 1; i <= n; i++) {
        indegree[parent[i]]++;
    }
    queue<int> pops;
    vector<bool> removed(n+1);
    for (int i = 1; i <= n; i++) if (!indegree[i]) pops.push(i);
    int left = n - 1;
    while (left > k) {
        //find one to pop off
        int f  = pops.front();
        pops.pop();
        removed[f] = true;
        indegree[parent[f]]--;
        if (!indegree[parent[f]]) pops.push(parent[f]);
        left--;
    }
    //output
    cout << left << '\n';
    for (int i = 2; i <= n; i++) {
        if (!removed[i]) {
            pair<int,int> p = {i,parent[i]};
            cout << mp[p] << ' ';
        }
    }

    return 0;
}

