#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
const int maxn = 1e5+5;
int dp[maxn][2];

void madd(int& a, int b) {
    a = (a+b) % M;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    dp[0][0] = dp[0][1] = 1;
    for (int i = 1; i <= max(n,m); i++) {
        for (int k = 0; k < 2; k++) {
            dp[i][k] = dp[i-1][k^1];
            if (i > 1) madd(dp[i][k],dp[i-2][k^1]);
        }
    }
    int ans = dp[m][0];
    madd(ans,dp[m][1]);
    ans = (ans-2+M) % M;
    madd(ans,dp[n][0]);
    madd(ans,dp[n][1]);
    cout << ans << '\n';
}

