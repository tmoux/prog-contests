#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];

int mn, mx;

void dfs(int i, int p) {
    int leaves = 0;
    for (int j: adj[i]) if (j != p) {
        if (adj[j].size() == 1) ++leaves;
        dfs(j,i);
    }
    if (leaves > 1) mx -= (leaves-1);
}

int dist[2];
void dfs2(int i, int p, int d) {
    if (adj[i].size() == 1) {
        dist[d&1] = 1;
    }
    for (int j: adj[i]) if (j != p) {
        dfs2(j,i,d+1);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() > 1) {
            root = i;
            break;
        }
    }
    mn = 1, mx = n-1;
    dfs(root,root);
    dfs2(root,root,0);
    if (dist[0] && dist[1]) {
        mn = 3;
    }
    cout << mn << ' ' << mx << endl;
}
