#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5;
int n, m;
vector<int> adj[maxn];
vector<int> dir[maxn];
ll ans[maxn];

void root(int i, int p) {
    for (int j: adj[i]) {
        if (j == p) continue;
        dir[i].push_back(j);
        root(j,i);
    }
}

void dfs(int i, int p, int d, int x) {
    if (d < 0) return;
    ans[i] += x;
    for (int j: dir[i]) {
        dfs(j,i,d-1,x);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    root(1,1);
    cin >> m;
    while (m--) {
        int v, d, x; cin >> v >> d >> x;
        dfs(v,v,d,x);
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i!=n];
    }

    return 0;
}

