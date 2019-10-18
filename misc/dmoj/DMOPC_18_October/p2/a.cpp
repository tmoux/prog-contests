#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, m;
int a[maxn][maxn], dp[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) dp[i][j] = a[i][j];
            else if (i == 0) dp[i][j] = dp[i][j-1] + a[i][j];
            else if (j == 0) dp[i][j] = dp[i-1][j] + a[i][j];
            else dp[i][j] = a[i][j] + min(dp[i-1][j],dp[i][j-1]);
        }
    }
    cout << dp[n-1][m-1] << '\n';
}

