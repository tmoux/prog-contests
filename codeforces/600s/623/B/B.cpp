#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <set>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1000005;
const ll INF = 9e18;
int A[maxn];
int n, a, b;
ll dp[maxn][3]; //0 is not started, 1 is started, 2 is already done

ll f(int i, int m, int p) {
    if (dp[i][m] >= 0) return dp[i][m];
    if (i == n) return 0;
    dp[i][m] = INF;
    if (m == 0) {
        dp[i][m] = min(dp[i][m],f(i+1,1,p) + a);
        if (A[i] % p == 0) {
            dp[i][m] = min(dp[i][m],f(i+1,m,p));
        }
        if ((A[i] + 1) % p == 0 || (A[i] - 1) % p == 0) {
            dp[i][m] = min(dp[i][m],f(i+1,m,p) + b);
        }
        return dp[i][m];
    }
    if (m == 1) {
        dp[i][m] = min(dp[i][m],f(i+1,1,p) + a);
        if (A[i] % p == 0) {
            dp[i][m] = min(dp[i][m],f(i+1,2,p));
        }
        if ((A[i] + 1) % p == 0 || (A[i] - 1) % p == 0) {
            dp[i][m] = min(dp[i][m],f(i+1,2,p) + b);
        }
        return dp[i][m];
    }
    if (m == 2) {
        if (A[i] % p == 0) {
            dp[i][m] = min(dp[i][m],f(i+1,2,p));
        }
        if ((A[i] + 1) % p == 0 || (A[i] - 1) % p == 0) {
            dp[i][m] = min(dp[i][m],f(i+1,2,p) + b);
        }
        return dp[i][m];
    }

}

void factor(int i, set<int>& factors) {
    for (int j = 2; j*j <= i; j++) {
        if (i % j == 0) {
            factors.insert(j);
            while (i % j == 0) i /= j;
            if (i != 1) {
                factor(i,factors);
            }
            return;
        }
    }
    factors.insert(i);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    set<int> factors;
    factor(A[0],factors);
    factor(A[n-1],factors);

    ll minans = INF;
    for (int i: factors) {
        memset(dp,-1,sizeof(dp));
        minans = min(minans,f(0,0,i));
        //cout << i << ' ' << f(0,0,i) << '\n';
    }
    cout << minans << '\n';

    return 0;
}
	

