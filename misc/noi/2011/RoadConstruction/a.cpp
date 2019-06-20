#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n;
vector<pair<int,int>> adj[maxn];

ll ans = 0;

int sub[maxn];
void DFS(int i, int p) {
    sub[i] = 1;
    for (auto j: adj[i]) {
        if (j.first == p) continue;
        DFS(j.first,i);
        sub[i] += sub[j.first];
    }
    for (auto j: adj[i]) {
        if (j.first == p) continue;
        ans += 1LL*j.second*(abs(sub[j.first]-(n-sub[j.first])));
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        int w; cin >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    DFS(1,1);
    cout << ans << '\n';
}

