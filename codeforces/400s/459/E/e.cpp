#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
struct Edge
{
    int u, v, w;
} edges[maxn];

int dp[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges[i] = {u,v,w};
    }
    sort(edges,edges+m,[](auto& a, auto& b) {
            return a.w < b.w;
            });
    int ans = 0;
    vector<pair<int,int>> v;
    for (int i = 0; i < m; i++) {
        Edge e = edges[i];
        if (e.w > edges[i-1].w) {
            for (auto p: v) {
                dp[p.first] = max(dp[p.first],p.second);
            }
            v.clear();
        }
        int d = dp[e.u] + 1;
        //cout << e.u << ' ' << e.v << ": " << d << '\n';
        ans = max(ans,d);
        v.push_back({e.v,d});
    }
    cout << ans << '\n';
}

