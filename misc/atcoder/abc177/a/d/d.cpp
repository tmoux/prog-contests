#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, m;
vector<int> adj[maxn];
bool vis[maxn];
int comp[maxn];

void dfs(int i, int pt) {
    comp[pt]++;
    vis[i] = true;
    for (int j: adj[i]) {
        if (!vis[j]) {
            dfs(j,pt);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int pt = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i,pt);
            ans = max(ans,comp[pt]);
            pt++;
        }
    }
    cout << ans << '\n';
}
