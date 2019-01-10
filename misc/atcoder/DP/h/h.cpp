#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int H, W;
char grid[maxn][maxn];
const int M = 1e9+7;

void madd(int& a, int b) {
    a = (a+b) % M;
}

int dp[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> H >> W;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
        }
    }

    dp[H-1][W-1] = 1;
    for (int i = H - 1; i >= 0; i--) {
        for (int j = W - 1; j >= 0; j--) {
            if (grid[i+1][j] != '#') madd(dp[i][j],dp[i+1][j]);
            if (grid[i][j+1] != '#') madd(dp[i][j],dp[i][j+1]);
        }
    }
    cout << dp[0][0] << '\n';

    return 0;
}

