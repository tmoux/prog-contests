#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 85;
int n, K, m;

vector<pair<int,int>> adj[maxn];
int dp[maxn][maxn][maxn][maxn]; //[l][r][i][k]

int f(int l, int r, int i, int k) {
    int& res = dp[l][r][i][k];
    if (res != -1) return res;
    if (k == 0) return 0;
    res = 2e9+9;
    for (auto p: adj[i]) {
        int j = p.first;
        int c = p.second;
        if (l < j && j < r) {
            if (j < i) {
                res = min(res,c+f(l,i,j,k-1));
            }
            else if (j > i) {
                res = min(res,c+f(i,r,j,k-1));
            }
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> K >> m;
    for (int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c;
        adj[u].push_back({v,c});
    }
    memset(dp,-1,sizeof dp);
    int ans = 2e9+9;
    for (int i = 1; i <= n; i++) {
        ans = min(ans,f(0,n+1,i,K-1));
    }
    cout << (ans>=2e9?-1:ans) << '\n';
}

