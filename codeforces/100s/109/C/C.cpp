#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, dp1[maxn], dp2[maxn], sub_size[maxn];
struct Edge {int to; bool luck;};
vector<Edge> adj[maxn];
inline bool isLucky(int x) {
    for (; x; x /= 10) 
        if (x % 10 != 4 && x % 10 != 7) return false;
    return true;
}

int dfs_prep(int i, int p) {
    sub_size[i] = 1;
    for (Edge e: adj[i]) {
        if (e.to == p) continue;
        sub_size[i] += dfs_prep(e.to,i);
    }
    return sub_size[i];
}

void dfs1(int i, int p) {
    for (Edge e: adj[i]) {
        if (e.to == p) continue;
        dfs1(e.to,i);
        if (e.luck) dp1[i] += sub_size[e.to];
        else dp1[i] += dp1[e.to];
    }
}

void dfs2(int i, int p) {
    for (Edge e: adj[i]) {
        if (e.to == p) continue;
        if (e.luck) dp2[e.to] = n - sub_size[e.to];
        else dp2[e.to] = dp2[i] + dp1[i] - dp1[e.to];
        dfs2(e.to,i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b, w; cin >> a >> b >> w;
        bool is = isLucky(w);
        adj[a].push_back({b,is});
        adj[b].push_back({a,is});
    }
    dfs_prep(1,1);
    dfs1(1,1);
    dfs2(1,1);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += 1LL*dp1[i]*(dp1[i]-1) + 1LL*dp2[i]*(dp2[i]-1) + 2LL*dp1[i]*dp2[i];
    }
    cout << ans << '\n';

    return 0;
}

