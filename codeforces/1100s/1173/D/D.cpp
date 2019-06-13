#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, M = 998244353;
int n;
vector<int> adj[maxn];
int fac[maxn];
void madd(int& a, int b) {
    a = (a+b) % M;
}
ll mult(int a, int b) {
    return (1LL*a*b) % M;
}

int sub_size[maxn];

int dfs_size(int i, int p) {
    sub_size[i] = 1;
    for (int j: adj[i]) {
        if (j == p) continue;
        sub_size[i] += dfs_size(j,i);
    }
    return sub_size[i];  
}

int dfs(int i, int p) {
    int res = 1;
    int num = 0;
    for (int j: adj[i]) {
        if (j == p) continue;
        res = mult(res,dfs(j,i));
        num++;
    }
    if (i != 1) num++;
    res = mult(res,fac[num]);
    //cout << i << ": " << res << '\n';
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = mult(i,fac[i-1]);
    }
    dfs_size(1,1);
    int ans = dfs(1,1);
    ans = mult(ans,n);
    cout << ans << '\n';
}

