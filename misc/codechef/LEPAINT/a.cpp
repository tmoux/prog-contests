#include <bits/stdc++.h>
using namespace std;
using ll = long long;

double dp[55][55][105];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int N, C, K; cin >> N >> C >> K;
        for (int i = 0; i < 55; i++) {
            for (int j = 0; j < 55; j++) {
                for (int c = 0; c < 105; c++) {
                    dp[i][j][c] = 0;
                }
            }
        }
        for (int i = 1; i <= N; i++) {
            dp[0][i][1] = 1;
        }
        for (int i = 1; i <= K; i++) {
            int l, r; cin >> l >> r;
            for (int j = 1; j <= N; j++) {
                for (int c = 0; c < C; c++) {
                    if (l <= j && j <= r) {
                        for (int c2 = 0; c2 < C; c2++) {
                            dp[i][j][(c*c2)%C] += dp[i-1][j][c]/(2*C);
                        }
                        dp[i][j][c] += dp[i-1][j][c]/2.0;
                    }
                    else {
                        dp[i][j][c] += dp[i-1][j][c];
                    }
                }
            }
        }
        double ans = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < C; j++) {
                ans += j*dp[K][i][j];
            }
        }
        cout << fixed << setprecision(10) << ans << '\n';
    }
}

