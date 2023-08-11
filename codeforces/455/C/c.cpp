#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, m, q;
int parent[maxn];
int dia[maxn];
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}
void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] < parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
    dia[x] = max(max(dia[x],dia[y]),(int)ceil(dia[x]/2.0)+(int)ceil(dia[y]/2.0)+1);
}

vector<int> adj[maxn];
int dist = 0;
int u = 0;
void DFS(int i, int p, int d) {
    if (d >= dist) {
        dist = d;
        u = i;
    }
    for (int j: adj[i]) {
        if (j == p) continue;
        DFS(j,i,d+1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> q;
    memset(parent,-1,sizeof parent);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        Union(a,b);
    }
    //calculate diameters
    vector<bool> seen(n+1);
    for (int i = 1; i <= n; i++) {
        int x = Find(i);
        if (!seen[x]) {
            dist = 0;
            DFS(x,x,0);
            DFS(u,u,0);
            dia[x] = dist;
            seen[x] = true;
            //cout << i << ' ' << x << ": " << dia[x] << '\n';
        }
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int x; cin >> x;
            cout << dia[Find(x)] << '\n';
        }
        else {
            int x, y; cin >> x >> y;
            Union(x,y);
        }
    }
}

