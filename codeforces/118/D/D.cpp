#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105, M = 1e8;
int n[2], k[2];
ll dp[2][maxn][maxn];

ll f(bool i, int j, int l) {
    if (j == 0 && l == 0) return dp[i][j][l] = 1;
    if (j < 0 || l < 0) return 0;
    ll& res = dp[i][j][l];
    if (res >= 0) return res;
    res = 0;
    for (int s = 1; s <= k[i]; s++) {
        res = (res + f(i,j-s,l-1)) % M;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    scanf("%d %d %d %d",n,n+1,k,k+1);
    memset(dp,-1,sizeof(dp));
    int ans = 0;
    for (int i = 1; i <= n[0]; i++) {
        ans = (ans + (f(0,n[0],i) * (f(1,n[1],i-1) + f(1,n[1],i+1) + 2*f(1,n[1],i)) % M) % M) % M;
    }
    printf("%d\n",ans);

    return 0;
}
	

