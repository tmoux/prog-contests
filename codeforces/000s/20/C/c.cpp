#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
struct Edge
{
    int to, w;
};
vector<Edge> adj[maxn];
const ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, w; cin >> a >> b >> w;
        if (a != b) {
            adj[a].push_back({b,w});
            adj[b].push_back({a,w});
        }
    }
    set<pair<ll,int>> s;
    vector<ll> dist(n+1,INF);
    s.insert({0,1});
    dist[1] = 0;
    vector<int> par(n+1,0);
    while (!s.empty()) {
        auto p = *s.begin();
        s.erase(s.begin());
        int u = p.second;
        for (Edge& e: adj[u]) {
            int v = e.to;
            ll w = e.w;
            if (dist[v] > dist[u] + w) {
                par[v] = u;
                if (dist[v] != INF) {
                    s.erase(s.find({dist[v],v}));
                }
                dist[v] = dist[u] + w;
                s.insert({dist[v],v});
            }
        }
    }
    if (dist[n] < INF) {
        vector<int> ans;
        int curr = n;
        do {
            ans.push_back(curr);
            curr = par[curr];
        } while (curr != 1);
        ans.push_back(1);
        for (int i = ans.size()-1; i >= 0; i--) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
    else {
        cout << -1 << '\n';
    }
}

