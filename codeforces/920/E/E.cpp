#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, parent[maxn];
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x), y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}

int deg[maxn];
set<int> adj[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) deg[i] = n-1;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        deg[x]--;
        deg[y]--;
        adj[x].insert(y);
        adj[y].insert(x);
    }
    int big = -1;
    for (int i = 1; i <= n; i++) {
        if (deg[i] > n/2) {
            if (big == -1) {
                big = Find(i);
            }
            else {
                Union(i,big);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] <= n/2) {
            for (int j = 1; j <= n; j++) {
                if (j == i || adj[i].count(j)) continue;
                Union(i,j);
            }
        }
    }

    set<int> comps;
    for (int i = 1; i <= n; i++) {
        comps.insert(Find(i));
    }
    cout << comps.size() << '\n';
    vector<int> ans;
    for (int i: comps) {
        ans.push_back(-parent[i]);
    }
    sort(ans.begin(),ans.end());
    for (int i: ans) {
        cout << i << ' ';
    }
    cout << '\n';

    return 0;
}

