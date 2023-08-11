#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int n, m, k;

ll dp[maxn][maxn];
ll A[maxn], pre[maxn];

ll sum(int l, int r) {
    return pre[r] - pre[l-1];
}

ll f(int i, int j) {
    if (dp[i][j] >= 0) return dp[i][j];
    if (j == 0) return dp[i][j] = 0;
    if (i + m - 1 > n) return dp[i][j] = 0;
    return dp[i][j] = max(sum(i,i+m-1) + f(i+m,j-1),f(i+1,j));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,-1,sizeof(dp));
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i-1] + A[i];
    }
    ll ans = f(1,k);
    cout << ans << '\n';

    return 0;
}
	

