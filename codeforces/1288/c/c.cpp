#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n, m;

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

int dp[2][maxn][maxn];

int sum(int o, int x1, int x2, int y1, int y2) {
    int res = dp[o][x2][y1];
    //cout << "adding " << x2 << ' ' << y1 << '\n';
    madd(res,M-dp[o][x1-1][y1]);
    //cout << "subbing " << x1-1 << ' ' << y1 << '\n';
    madd(res,M-dp[o][x2][y2+1]);
    //cout << "subbing " << x2 << ' ' << y2+1 << '\n';
    madd(res,dp[o][x1-1][y2+1]);
    //cout << "adding " << x1-1 << ' ' << y2+1 << '\n';
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    dp[0][1][n] = 1;
    for (int k = 1; k <= m; k++) {
        int o = k&1;
        for (int i = 1; i <= n; i++) {
            for (int j = n; j >= 1; j--) {
                madd(dp[o^1][i][j],dp[o^1][i][j+1]);
                madd(dp[o^1][i][j],dp[o^1][i-1][j]);
                madd(dp[o^1][i][j],M-dp[o^1][i-1][j+1]);
                //cout << k-1 << ": " << i << ' ' << j << ' ' << dp[o^1][i][j] << '\n';
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                dp[o][i][j] = sum(o^1,1,i,j,n);
                //cout << k << ": " << i << ' ' << j << ' ' << dp[o][i][j] << '\n';
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            madd(ans,dp[m&1][i][j]);
        }
    }
    cout << ans << '\n';
}

