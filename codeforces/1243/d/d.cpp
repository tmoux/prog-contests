#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
set<int> adj[maxn];
int deg[maxn];

  
int parent[maxn]; //memset to -1
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].insert(b);
        adj[b].insert(a);
        deg[a]++;
        deg[b]++;
    }
    pair<int,int> best = {maxn,-1};
    for (int i = 1; i <= n; i++) {
        best = min(best,make_pair(deg[i],i));
    }
    int st = best.second;
    for (int i = 1; i <= n; i++) {
        if (i == st || adj[st].count(i)) continue;
        Union(st,i);
    }
    for (int i: adj[st]) {
        for (int j = 1; j <= n; j++) {
            if (!adj[i].count(j)) {
                Union(i,j);
            }
        }
    }
    set<int> ans;
    for (int i = 1; i <= n; i++) {
        ans.insert(Find(i));
    }
    cout << ans.size()-1 << '\n';
}
