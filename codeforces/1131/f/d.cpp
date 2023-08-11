#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 150005;
int parent[maxn]; //memset to -1
int l[maxn], r[maxn];
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
    //join left to right
    r[x] = r[y];
}

int n;

vector<int> adj[maxn];

void dfs(int i, int p) {
    cout << i << ' ';
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        l[i] = r[i] = i;
    }
    for (int i = 0; i < n-1; i++) {
        int x, y; cin >> x >> y;
        int px = Find(x), py = Find(y);
        adj[l[px]].push_back(r[py]);
        adj[r[py]].push_back(l[px]);
        //cout << l[px] << ' ' << r[py] << endl;
        Union(x,y);
    }
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() == 1) {
            dfs(i,i);    
            cout << '\n';
            return 0;
        }
    }
}

