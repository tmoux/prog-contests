#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5e5+5;
int n, m;
vector<int> adj[maxn];
bool vis[maxn];

int par[maxn];
int depth[maxn];
vector<int> dlist[maxn];
void dfs2(int i, int p, int d) {
    par[i] = p; 
    depth[i] = d;
    dlist[d].push_back(i);
    vis[i] = true;
    for (int j: adj[i]) if (j != p) {
        if (vis[j]) continue;
        dfs2(j,i,d+1);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        vis[i] = false;
        par[i] = 0;
        depth[i] = 0;
        dlist[i].clear();
    }
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int rt = 1;
    dfs2(rt,rt,1);
    int target = (n+1)/2;
    bool foundpath = false;
    vector<int> path;
    for (int i = 1; i <= n; i++) {
        if (depth[i] >= target) {
            foundpath = true;
            int cur = i;
            while (true) {
                path.push_back(cur);
                if (cur == rt) break;
                else cur = par[cur];
            }
            break;
        }
    }
    if (foundpath) {
        cout << "PATH\n";
        cout << path.size() << '\n';
        for (auto i: path) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    else {
        vector<pair<int,int>> ans;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j+1 < dlist[i].size(); j += 2) {
                ans.push_back({dlist[i][j],dlist[i][j+1]});
            }
        }
        assert(ans.size()*2 >= target);
        cout << "PAIRING\n";
        cout << ans.size() << '\n';
        for (auto p: ans) {
            cout << p.first << ' ' << p.second << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
