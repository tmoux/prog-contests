#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n;
ll v[maxn];
vector<int> adj[maxn];
pair<ll,ll> f[maxn];

void dfs(int i, int par) {
    for (int j: adj[i]) {
        if (j == par) continue;
        dfs(j,i);
        f[i].first = max(f[i].first,f[j].first);
        f[i].second = min(f[i].second,f[j].second);
    }
    ll diff = -(f[i].first + f[i].second + v[i]);
    if (diff >= 0) {
        f[i].first += diff;
    }
    else {
        f[i].second += diff;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) 
        cin >> v[i];
    dfs(1,-1);
    cout << (f[1].first-f[1].second) << '\n';
    return 0;
}
	

