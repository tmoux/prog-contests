#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1005;
const ll INF = 1000000000000000000;
int n, m, x;
struct Edge
{
    int to, cost, time;
};
vector<Edge> adj[maxn];
ll dp[maxn][maxn]; //node/current cost

ll f(int i, int c) {
    if (dp[i][c] >= 0) return dp[i][c];
    if (c > x) {
        return INF;
    }
    if (i == n) {
        return dp[i][c] = 0LL;
    }
    dp[i][c] = INF;
    for (Edge e: adj[i]) {
        if (c+e.cost > x) continue;
        dp[i][c] = min(dp[i][c],(ll)e.time + f(e.to,c+e.cost));    
    }
    return dp[i][c];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> x;
    for (int i = 0; i < m; i++) {
        int u, v, c, t;
        cin >> u >> v >> c >> t;
        adj[u].push_back({v,c,t});
        adj[v].push_back({u,c,t});
    }
    memset(dp,-1,sizeof(dp));
    ll ans = f(1,0);
    cout << (ans == INF ? -1 : ans) << '\n';

    return 0;
}
	

