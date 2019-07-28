#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005, maxx = 10005, M = 1e9+7;
int n, a[maxn];

int dp[maxn][2*maxx];

void madd(int& a, int b) {
    a = (a+b) % M;
}
const int offset = 10000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    dp[0][0+offset] = 1;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = -10000; j <= 10000; j++) {
            madd(dp[i][j+offset],dp[i-1][j-a[i]+offset]);
            madd(dp[i][j+offset],dp[i-1][j+a[i]+offset]);
        }
        madd(ans,dp[i][0+offset]);
        madd(dp[i][0+offset],1);
    }
    cout << ans << '\n';
}

