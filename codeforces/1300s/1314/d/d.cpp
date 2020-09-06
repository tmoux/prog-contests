#include <bits/stdc++.h>
using namespace std;
using ll = long long;

random_device device;
mt19937 gen(device());
const int maxn = 85, INF = 2e9;
int n, k;
int a[maxn][maxn];
int color[maxn];

int dp[maxn][11];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    int ans = INF;
    for (int iter = 0; iter < 5000; iter++) {
        for (int i = 0; i < n; i++) {
            color[i] = gen()&1;
        }
        dp[0][0] = 0;
        for (int i = 1; i < n; i++) {
            dp[i][0] = INF;
        }
        for (int x = 1; x <= k; x++) {
            for (int i = 0; i < n; i++) {
                dp[i][x] = INF;
                for (int j = 0; j < n; j++) {
                    if (i == j) continue;
                    if (color[i] != color[j]) dp[i][x] = min(dp[i][x],dp[j][x-1]+a[j][i]);
                }
            }
        }
        ans = min(ans,dp[0][k]);
    }
    cout << ans << '\n';
}
