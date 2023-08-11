#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005, M = 1e9+7;
int n, d, a[maxn];
vector<int> adj[maxn];

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int f(int i, int p, int mn, int orig) {
    int res = 1;
    for (int j: adj[i]) {
        if (j == p || a[j] < mn || a[j] > mn+d) continue;
        if (a[j] == a[orig] && j < orig) continue;
        res = mult(res,f(j,i,mn,orig)+1);
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> d >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int x = f(i,i,a[i],i);
        ans = (ans + x) % M;
    }
    cout << ans << '\n';
}
