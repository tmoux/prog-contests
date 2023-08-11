#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 500;
const int MOD = 1e9+7;
int n, d, k;

int dp[maxn][2];

int f(int i, int b) {
    if (i < 0) return 0;
    if (dp[i][b] >= 0) return dp[i][b];
    if (i == 0 && b == 1) return dp[i][b] = 1;
    if (i == 0 && b == 0) return dp[i][b] = 0;
    dp[i][b] = 0;
    for (int j = 1; j <= k; j++) {
        if (j < d) {
            dp[i][b] = (dp[i][b] + f(i-j,b)) % MOD;
        }
        else {
            dp[i][b] = (dp[i][b] + f(i-j,1)) % MOD;
        }
    }
    return dp[i][b];
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> d;
    memset(dp,-1,sizeof(dp));
    cout << f(n,0) << '\n';

    return 0;
}
	

