#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int maxn = 10000007;
const int MOD = 1e9+7;

int dp[maxn][4];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (j != k) {
                    dp[i+1][k] = (dp[i+1][k] + dp[i][j]) % MOD;
                }
            }
        }
    }

    int ans = dp[n][0];
    cout << ans << '\n';

    /*
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 4; j++) {
            cout << i << ' ' << j << ' ' << dp[i][j] << '\n';
        }
    }
    */

    return 0;
}
	

