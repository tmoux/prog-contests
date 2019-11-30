#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5;
int n;
ll w[maxn];
struct Edge
{
    int to, w;
};
vector<Edge> adj[maxn];

bool blocked[maxn];
int sub_size[maxn];

int dfsSize(int i, int p) {
    sub_size[i] = 1;
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        sub_size[i] += dfsSize(e.to,i);
    }
    return sub_size[i];
}
int getCentroid(int i, int p, int compSize) {
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        if (sub_size[e.to] * 2 > compSize) return getCentroid(e.to,i,compSize);
    }
    return i;
}

ll ans = 0;

ll dp1[maxn], dp2[maxn];

void dfs1(int i, int p) {
    dp1[i] = w[i];
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        dfs1(e.to,i);
        dp1[i] = max(dp1[i],dp1[e.to]-e.w);
    }
}

void dfs2(int i, int p, ll d) {
    if (d < 0) return;
    d += w[i];
    ans = max(ans,d);
    //cout << i << ": " << dp2[i] << '\n';
    for (Edge e: adj[i]) {
        if (e.to == p || blocked[e.to]) continue;
        dfs2(e.to,i,d-e.w);
    }
}

void solve(int centroid) {
    dp1[centroid] = w[centroid];
    //cout << "centroid = " << centroid << '\n';
    for (Edge e: adj[centroid]) {
        //cout << "testing subtree " << e.to << '\n';
        //cout << "dp1[centroid] = " << dp1[centroid] << '\n';
        dfs2(e.to,centroid,dp1[centroid]-e.w);
        dfs1(e.to,centroid);
        dp1[centroid] = max(dp1[centroid],dp1[e.to]-e.w);
    }
    dp1[centroid] = w[centroid];
    for (auto it = adj[centroid].rbegin(); it != adj[centroid].rend(); ++it) {
        Edge e = *it;
        dfs2(e.to,centroid,dp1[centroid]-e.w);
        dfs1(e.to,centroid);
        dp1[centroid] = max(dp1[centroid],dp1[e.to]-e.w);
    }
    ans = max(ans,dp1[centroid]);
    //cout << "ans = " << ans << '\n';
}

void decomp(int i) {
    int compSize = dfsSize(i,i);
    int centroid = getCentroid(i,i,compSize);
    blocked[centroid] = true;
    solve(centroid);
    for (Edge e: adj[centroid]) {
        if (blocked[e.to]) continue;
        decomp(e.to);
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 0; i < n - 1; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    decomp(1);
    cout << ans << '\n';
    return 0;
}

