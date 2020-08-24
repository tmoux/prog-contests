#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int N;
vector<int> adj[maxn];
int P[maxn], A[maxn], B[maxn];
int ans[maxn];
bool blocked[maxn];

void dfs(int i, int p, int pop, int day) {
    int take = min(pop,B[i]);
    B[i] -= take;
    if (B[i] == 0 && ans[i] == -1) ans[i] = day;
    for (int j: adj[i]) if (j != p) {
        if (blocked[j]) continue;
        dfs(j,i,pop,day);
    }
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        adj[i].clear();
        ans[i] = -1;
        blocked[i] = false;
    }
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= N; i++) cin >> P[i];
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) cin >> B[i];
    for (int i = 1; i <= N; i++) {
        dfs(P[i],P[i],A[P[i]],i);
        blocked[P[i]] = true;
    }
    for (int i = 1; i <= N; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
