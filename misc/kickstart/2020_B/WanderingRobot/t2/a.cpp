#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        cout << "Case #" << q << ": ";
        int W, H, L, U, R, D;
        cin >> W >> H >> L >> U >> R >> D;
        --L; --U; --R; --D;
        if (W <= 300 && H <= 300) {
            vector<vector<double>> dp(W,vector<double>(H));
            auto in = [W,H,L,U,R,D] (int x, int y) {
                return L <= x && x <= R && U <= y && y <= D;
            };
            auto valid = [W,H,L,U,R,D] (int x, int y) {
                return 0 <= x && x < W && 0 <= y && y < H;
            };
            for (int x = 0; x < W; x++) {
                for (int y = 0; y < H; y++) {
                    if (x == 0 && y == 0) {
                        dp[x][y] = 1;
                    }
                    else if (in(x,y)) dp[x][y] = 0;
                    else if (x == 0) {
                        dp[x][y] = dp[x][y-1];
                    }
                    else if (y == 0) {
                        dp[x][y] = dp[x-1][y];
                    }
                    else {
                        dp[x][y] = 0.5*(dp[x-1][y]+dp[x][y-1]);
                    }
                }
            }
            double ans = 0;
            int x = L-1, y = D+1;
            while (x >= 0 && y < H) {
                ans += dp[x][y];
                x--; y++;
            }
            x = R+1, y = U-1;
            while (x < W && y >= 0) {
                ans += dp[x][y];
                x++; y--;
            }
            cout << fixed << setprecision(10) << ans << '\n';
        }
    }
}

