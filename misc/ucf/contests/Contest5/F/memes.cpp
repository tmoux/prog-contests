#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int n, R;
ll dp[maxn][maxn];
int rec[maxn], dank[maxn];

ll f(int i, int d) {
    if (dp[i][d] >= 0) return dp[i][d];
    if (i == n) return 0LL;
    if (d + rec[i] > R) {
        return dp[i][d] = f(i+1,d);
    }
    return dp[i][d] = max((ll)f(i+1,d),(ll)dank[i] + f(i+1,d+rec[i]));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> R;
    for (int i = 0; i < n; i++) {
        cin >> rec[i] >> dank[i];
    }
    memset(dp,-1,sizeof(dp));
    ll ans = f(0,0);
    cout << ans << '\n';

    return 0;
}
	

