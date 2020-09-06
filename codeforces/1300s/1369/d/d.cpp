#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
const int maxn = 2e6+6;
ll dp[2][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    dp[0][1] = dp[1][1] = dp[0][2] = dp[1][2] = 0;
    for (int i = 3; i <= 2000000; i++) {
        dp[1][i] = (2*dp[0][i-2] + dp[0][i-1]) % M;
        dp[0][i] = (4 + 2*dp[1][i-2] + dp[1][i-1]) % M;
        if (i % 3 == 2) dp[0][i] = dp[1][i];
    }
    /*
    for (int i = 1; i <= 100; i++) {
        cout << i << ": " << dp[0][i] << ' ' << dp[1][i] << ' ' << (dp[0][i] > dp[1][i]) << '\n';
    }
    */
    while (t--) {
        int n; cin >> n;
        cout << dp[0][n] << '\n'; 
    }
}
