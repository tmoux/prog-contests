#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n;
int a[maxn][maxn];
int dp[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) 
            cin >> a[i][j];
    }
    for (int i = n-1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = a[i][j] + max(dp[i+1][j],dp[i+1][j+1]);
        }
    }
    cout << dp[0][0] << '\n';
}

