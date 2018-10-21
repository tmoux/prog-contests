#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

const int MOD = 1000000007;
const int maxn = 4005;
ll co[maxn][maxn];
ll be[maxn][maxn];
int n;

ll bell(int i) {
    if (i == 0) return 1LL;
    return be[i-1][i-1];
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    co[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        co[i][0] = 1;
        for (int j = 1; j <= i; j++) {
           co[i][j] = (co[i-1][j-1] + co[i-1][j]) % MOD;
        }
    }

    be[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        be[i][0] = be[i-1][i-1];
        for (int j = 1; j <= i; j++) {
            be[i][j] = (be[i-1][j-1] + be[i][j-1]) % MOD;
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + co[n][i]*bell(i)) % MOD;
    }
    cout << ans << '\n';
    


    return 0;
}
	

