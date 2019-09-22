#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;
int s;
int w[maxn];
set<int> adj[maxn];
int deg[maxn];
ll csum[maxn];
bool vis[maxn];
int par[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
        ++deg[u];
        ++deg[v];
    }
    cin >> s;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (i != s && deg[i] == 1) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int f = q.front(); q.pop();
        vis[f] = true;
        int p = *adj[f].begin();
        csum[p] = max(csum[p],csum[f] + w[f]);
        for (int j: adj[f]) {
            if (adj[j].count(f)) adj[j].erase(f);
            if (adj[j].size() == 1 && j != s) {
                q.push(j);
            }
        }
    }
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) res += w[i];
    }
    ll bestLeaf = 0;
    for (int i = 1; i <= n; i++) {
        bestLeaf = max(bestLeaf,csum[i]);
        //cout << i << ": " << csum[i] << '\n';
    }
    cout << (res + bestLeaf) << '\n';
}
