#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1e9+7;
ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}
int n, k;
struct Edge
{
    int to;
    bool isGood;
};
vector<Edge> adj[maxn];

bool vis[maxn];

void DFS(int i, int& sz) {
    sz++;
    vis[i] = true;
    for (Edge e: adj[i]) {
        if (e.isGood || vis[e.to]) continue;
        DFS(e.to,sz);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        int x; cin >> x;
        adj[u].push_back({v,x});
        adj[v].push_back({u,x});
    }

    ll totalbad = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            int sz = 0;
            DFS(i,sz);
            totalbad = (totalbad + modexp(sz,k)) % M;
        }
    }

    ll ans = modexp(n,k);
    ans = (ans - totalbad + M) % M;
    cout << ans << '\n';
}

