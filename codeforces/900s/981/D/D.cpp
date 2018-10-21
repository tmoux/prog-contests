#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 55;
int n, k;
ll A[maxn], pref[maxn];
bool dp[maxn][maxn];

bool check(ll x) {
    memset(dp,0,sizeof(dp));
    dp[0][0] = 1;
    //dp[i][j] is if using the first i bookshelves and the first j elements, they can AND sum to x, the target value.
    //This is possible if for some kk 1 <= kk <= i, dp[kk-1][j-1] is possible and the (sum from kk-i) & x equals x.
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            for (int kk = i; kk >= 1; kk--) {
                if (dp[kk-1][j-1] && ((pref[i] - pref[kk-1]) & x) == x) {
                    dp[i][j] = 1;
                }
            }
        }
    }
    return dp[n][k];
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        pref[i] = pref[i-1] + A[i];
    }
    ll ans = 0LL;
    for (int i = maxn; i >= 0; i--) {
        if (check(ans + (1LL << i))) {
            ans += (1LL << i);
        }
    }
    //output
    cout << ans << '\n';


    return 0;
}
	

