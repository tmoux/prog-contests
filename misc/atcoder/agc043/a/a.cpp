#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int H, W;
char grid[maxn][maxn];
int dp[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> H >> W;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (i == 0 && j == 0) dp[i][j] = (grid[i][j]=='#');
            else if (i == 0) dp[i][j] = dp[i][j-1] + (grid[i][j] == '#' && grid[i][j] != grid[i][j-1]);
            else if (j == 0) dp[i][j] = dp[i-1][j] + (grid[i][j] == '#' && grid[i][j] != grid[i-1][j]);
            else dp[i][j] = min(dp[i][j-1]+(grid[i][j] == '#' && grid[i][j]!=grid[i][j-1]),dp[i-1][j]+(grid[i][j] == '#' && grid[i][j]!=grid[i-1][j]));
        }
    }
    int ans = dp[H-1][W-1];
    cout << ans << '\n';
}

