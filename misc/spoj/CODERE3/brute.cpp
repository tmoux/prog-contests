#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int maxn = 1005;
int n, A[maxn];
int dp[2][maxn][maxn];
 
int f(bool is, int i, int j) {
    //false for increasing, true for decreasing
    if (i > n) return 0;
    if (dp[is][i][j] >= 0) return dp[is][i][j];
    int& res = dp[is][i][j];
    res = f(is,i+1,j);
    if (A[i] < A[j]) {
        res = max(res,1+f(1,i+1,i));
    }
    else if (A[i] > A[j] && !is) {
        res = max(res,1+f(is,i+1,i));
    }
    return res;
}
 
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];
    A[0] = -999;
    memset(dp,-1,sizeof dp);
    int ans = f(0,1,0);
    cout << ans << '\n';
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
