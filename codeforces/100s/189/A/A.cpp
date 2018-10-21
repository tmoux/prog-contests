#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 10000;
int dp[maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, a, b, c; cin >> n >> a >> b >> c;
    memset(dp,-1,sizeof(dp));
    dp[0] = 0;
    for (int i = 0; i <= n; i++) {
        if (dp[i] >= 0) {
            dp[i+a] = max(dp[i+a],dp[i]+1);
            dp[i+b] = max(dp[i+b],dp[i]+1);
            dp[i+c] = max(dp[i+c],dp[i]+1);
        }
    }
    cout << dp[n] << '\n';


    return 0;
}
	

