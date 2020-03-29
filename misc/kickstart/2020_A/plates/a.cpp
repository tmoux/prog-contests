#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55, maxk = 35;
int n, k, p;
int a[maxn][maxk];
int dp[maxn][maxn*maxk];

int f(int i, int j) {
    int& res = dp[i][j];
    if (res != -1) return res;
    if (i == n) {
        if (j == p) return res = 0;
        else return res = -2e9;
    }
    res = f(i+1,j);
    for (int kk = 1; kk <= k; kk++) {
        if (j+kk > p) continue;
        res = max(res,a[i][kk]+f(i+1,j+kk));
    }
    return res;
}

int main() {
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        cout << "Case #" << q << ": ";
        cin >> n >> k >> p;
        memset(a,0,sizeof a);
        memset(dp,-1,sizeof dp);
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                cin >> a[i][j];
                if (j > 0) a[i][j] += a[i][j-1];
                //cout << a[i][j] << ' ';
            }
            //cout << '\n';
        }
        int ans = f(0,0);
        cout << ans << '\n';
    }
}
