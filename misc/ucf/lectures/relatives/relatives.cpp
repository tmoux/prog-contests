#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 16;
const int INF = 999999999;
int n;
int grid[maxn][maxn];
int dp[maxn][1 << maxn];

int popcount(int mask) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
            res++;
        }
    }
    return res;
}

int f(int i, int mask) {
    if (dp[i][mask] >= 0) return dp[i][mask];
    int pop = popcount(mask);
    if (pop == n - 1) {
        return dp[i][mask] = grid[i][0];
    }

    dp[i][mask] = INF;
    for (int j = 1; j < n; j++) {
        if (!(mask & (1 << j))) {
            dp[i][mask] = min(dp[i][mask],grid[i][j] + f(j,mask|(1<<j)));
        }
    }
    //cout << i << ' ' << mask << ' ' << dp[i][mask] << ' ' << pop << '\n';
    return dp[i][mask];
}

void solve() {
    cin >> n;
    memset(dp,-1,sizeof(dp));
    memset(grid,0,sizeof(grid));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double c; cin >> c;
            grid[i][j] = (int)(c*100);
        }
    }
    int ans = f(0,0);
    cout << fixed << setprecision(2) << (double)ans/100 << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
	

