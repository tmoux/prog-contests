#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 52;
int n;
char grid[maxn][maxn];
int pre[maxn][maxn];

int dp[maxn][maxn][maxn][maxn];

int cnt(int x1, int y1, int x2, int y2) {
    return pre[x2][y2] - pre[x1-1][y2] - pre[x2][y1-1] 
        + pre[x1-1][y1-1];
}

int f(int x1, int y1, int x2, int y2) {
    int& res = dp[x1][y1][x2][y2];
    if (res >= 0) return res;
    int c = cnt(x1,y1,x2,y2);
    if (c == 0) return res = 0;
    res = max(x2-x1+1,y2-y1+1);
    for (int i = x1; i < x2; i++) {
        res = min(res,f(x1,y1,i,y2) + f(i+1,y1,x2,y2));
    }
    for (int i = y1; i < y2; i++) {
        res = min(res,f(x1,y1,x2,i) + f(x1,i+1,x2,y2));
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
            pre[i][j] = grid[i][j] == '#' ? 1 : 0;
            pre[i][j] += pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
        }
    }
    memset(dp,-1,sizeof dp);
    int ans = f(1,1,n,n);
    cout << ans << '\n';
}

