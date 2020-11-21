#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
const ll INF = 1e12;
int N, M;
struct Edge
{
    int to, weight;
};
vector<Edge> adj[maxn];

vector<ll> dijkstra(int source) {
    vector<ll> dist(N+1,INF);
    dist[source] = 0;
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    pq.push({0LL,source});
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (d > dist[u]) continue;
        for (Edge& e: adj[u]) {
            int v = e.to;
            ll weight = e.weight;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v],v});
            }
        }
    }
    return dist;
}

ll dist[10][10];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b, t; cin >> a >> b >> t;
        adj[a].push_back({b,t});
        adj[b].push_back({a,t});
    }
    set<int> s = {1};
    for (int i = 0; i < 7; i++) {
        int a; cin >> a;
        s.insert(a);
    }
    map<int,int> mp;
    int pt = 0;
    for (auto i: s) {
        mp[i] = pt;
        pt++;
    }
    for (int i = 0; i < pt; i++) {
        for (int j = 0; j < pt; j++) {
            dist[i][j] = INF;
        }
    }
    for (int i: s) {
        auto d = dijkstra(i);
        for (auto j: s) {
            dist[mp[i]][mp[j]] = d[j];
        }
    }

    vector<int> p;
    for (auto i: s) if (i != 1) p.push_back(mp[i]);
    sort(p.begin(),p.end());
    ll ans = INF;
    do {
        ll tr = 0;
        int cur = 0;
        for (int i = 0; i < p.size(); i++) {
            tr += dist[cur][p[i]];
            cur = p[i];
        }
        ans = min(ans,tr);
    } while (next_permutation(p.begin(),p.end()));
    cout << (ans >= INF ? -1 : ans) << '\n';
    /*
    for (int i = 0; i < pt; i++) {
        for (int j = 0; j < pt; j++) {
            cout << i << ' ' << j << ": " << dist[i][j] << endl;
        }
    }
    */
}
