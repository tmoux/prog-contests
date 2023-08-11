#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
struct Edge {
    int to, wt;
};
vector<Edge> adj[maxn];

int cnt[maxn];
ll G = 0, B = 0;
void dfs(int i, int p, int wt) {
    cnt[i] = 1;
    for (auto e: adj[i]) {
        if (e.to == p) continue;
        dfs(e.to,i,e.wt);
        cnt[i] += cnt[e.to];
    }
    if (cnt[i]&1) G += wt;
    B += 1LL*wt*min(cnt[i],2*n-cnt[i]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= 2*n; i++) {
            adj[i].clear();
            cnt[i] = 0;
        }
        for (int i = 0; i < 2*n-1; i++) {
            int a, b, t; cin >> a >> b >> t;
            adj[a].push_back({b,t});
            adj[b].push_back({a,t});
        }
        G = B = 0;
        dfs(1,1,0);
        cout << G << ' ' << B << '\n';
    }
}

