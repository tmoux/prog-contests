#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const ll maxn = 1050;
const ll MOD = 998244353;
ll n, A[maxn];

ll choose[maxn][maxn];
ll dp[maxn];

ll f(ll i) {
    if (i == n) return 1;
    if (i >= n) return 0;
    if (dp[i] >= 0) return dp[i];
    if (A[i] <= 0 || A[i] >= n) {
        return dp[i] = f(i+1);
    }
    dp[i] = f(i+1);
    for (ll j = i + A[i]; j < n; j++) {
        dp[i] = (dp[i] + choose[j-i-1][A[i]-1]*f(j+1)) % MOD;
    }
    return dp[i];
}

void fillc() {
    choose[0][0] = 1;
    for (ll i = 1; i < maxn; i++) {
        for (ll j = 0; j <= i; j++) {
            if (j == 0) choose[i][j] = 1;
            else choose[i][j] = (choose[i-1][j-1] + choose[i-1][j]) % MOD;
        }
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,-1,sizeof(dp));
    fillc();
    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> A[i];
    }
    
    ll ans = f(0);
    cout << (ans - 1 + MOD) % MOD << '\n';

    return 0;
}
	

