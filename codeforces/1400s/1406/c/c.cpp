#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
vector<int> adj[maxn];
int sub_size[maxn];
int mx_size[maxn];
int depth[maxn];

int dfs(int i, int p) {
    sub_size[i] = 1;
    mx_size[i] = 0;
    depth[i] = depth[p]+1;
    for (int j: adj[i]) if (j != p) {
        int sub = dfs(j,i);
        sub_size[i] += sub;
        mx_size[i] = max(mx_size[i],sub);
    }
    mx_size[i] = max(mx_size[i],n-sub_size[i]);
    return sub_size[i];
}
pair<int,int> findLeaf(int i, int p) {
    if (adj[i].size() == 1) {
        return {i,p};
    }
    for (auto j: adj[i]) if (j != p) {
        return findLeaf(j,i);
    }
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        sub_size[i] = 0;
        mx_size[i] = 0;
        depth[i] = 0;
    }
    for (int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1,1);
    int least = n+1;
    vector<int> centroids;
    for (int i = 1; i <= n; i++) {
        if (mx_size[i] < least) {
            least = mx_size[i];
            centroids = {i};
        }
        else if (mx_size[i] == least) {
            centroids.push_back(i);
        }
    }
    if (centroids.size() == 1) {
        int j = adj[1][0];
        cout << 1 << ' ' << j << '\n';
        cout << 1 << ' ' << j << '\n';
    }
    else {
        assert(centroids.size() == 2);
        int u = centroids[0], v = centroids[1];
        if (depth[u] < depth[v]) swap(u,v);
        //cout << "centroids " << u << ' ' << v << '\n';
        pair<int,int> leaf = findLeaf(u,v);
        cout << leaf.first << ' ' << leaf.second << '\n';
        cout << leaf.first << ' ' << v << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
