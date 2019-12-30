#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005;
int n, m;
vector<int> adj[maxn];
map<pair<int,int>,int> mp;
int vis[maxn]; //0 = not visited, 1 = visited before, 2 = on stack
int ans[maxn];

int k = 1;

void dfs(int i) {
    vis[i] = 2;
    for (int j: adj[i]) {
        if (vis[j] == 2) {
            ans[mp[make_pair(i,j)]] = 1;
            k = 2;
        }
        else if (vis[j] == 0) {
            dfs(j);
        }
    }
    vis[i] = 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        mp[make_pair(u,v)] = i;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i);
    }
    cout << k << '\n';
    for (int i = 0; i < m; i++) {
        cout << ans[i]+1 << ' ';
    }
    cout << '\n';
}

