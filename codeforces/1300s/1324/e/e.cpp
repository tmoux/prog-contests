#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int n, h, l, r;
int a[maxn];

int dp[maxn][maxn];

void amax(int& a, int b) {
    a = max(a,b);
}

int good(int x) {
    return (l <= x && x <= r) ? 1 : 0;
}

int main() {
    cin >> n >> h >> l >> r;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < h; j++) {
            dp[i][j] = good(j)+max(dp[i+1][(j+a[i+1]-1)%h],dp[i+1][(j+a[i+1])%h]);
            //printf("[%d][%d]: %d\n",i,j,dp[i][j]);
        }
    }
    cout << max(dp[1][a[1]-1],dp[1][a[1]]) << endl;
}
