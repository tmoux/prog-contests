#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, q;
ll w;

ll dist[5005][5005];
vector<int> adj[maxn];
vector<pair<int,int>> edges;

ll farthestDist = 0;
int nxt = -1;

void dfs(int i, int p, ll d) {
    if (d >= farthestDist) {
        farthestDist = d;
        nxt = i;
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i,d+dist[i][j]);
    }
}

ll getDiameter(int i) {
    farthestDist = 0;    
    nxt = -1;
    dfs(i,i,0);
    assert(nxt != -1);
    dfs(nxt,nxt,0);
    return farthestDist;
}

int deg[maxn];
struct Edge
{
    int to;
    ll wt;
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q >> w;
    if (n <= 5000) {
        for (int i = 0; i < n-1; i++) {
            int a, b;
            ll c;
            cin >> a >> b >> c;
            adj[a].push_back(b);
            adj[b].push_back(a);
            dist[a][b] = dist[b][a] = c;
            edges.push_back({a,b});
        }
        ll last = 0;
        while (q--) {
            int dj; cin >> dj;
            ll ej; cin >> ej;
            dj = (dj+last) % (n-1);
            ej = (ej+last) % w;
            int u = edges[dj].first;
            int v = edges[dj].second;
            dist[u][v] = dist[v][u] = ej;
            last = getDiameter(1);
            cout << last << '\n';
            /*
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    cout << i << ' ' << j << ": " << dist[i][j] << '\n';
                }
            }
            */
        }
    }
    else {
        vector<vector<Edge>> adj(n+1);
        vector<pair<pair<int,int>,ll>> edges;
        for (int i = 0; i < n - 1; i++) {
            int a, b; cin >> a >> b;
            ll c; cin >> c;
            adj[a].push_back({b,c});
            adj[b].push_back({a,c});
            deg[a]++;
            deg[b]++;
            edges.push_back({{a,b},c});
        }
        if (deg[1] == n-1) {
            multiset<ll> mul;
            for (auto p: edges) {
                mul.insert(p.second);
            }
            ll last = 0;
            while (q--) {
                int dj; cin >> dj;
                ll ej; cin >> ej;
                dj = (dj+last) % (n-1);
                ej = (ej+last) % (w);
                auto it = mul.find(edges[dj].second);
                mul.erase(it);
                edges[dj].second = ej;
                mul.insert(ej);

                last = (mul.size() == 1 ? *mul.rbegin() :
                       *prev(mul.end()) + *prev(prev(mul.end())));
                cout << last << '\n';
            }
        }
        else {
            assert(false);
        }
    }
}

