#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e3+4, maxk = 203;
int n, k;
int a[maxn];
ll dp[maxk][maxn][maxn];

ll f(int K, int l, int r)
{
    if (dp[K][l][r] != -1) return dp[K][l][r];
    
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    memset(dp,-1,sizeof dp);
    ll ans = f(k,1,n);
}

