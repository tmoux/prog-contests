#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5, sq = (int)(sqrt(2*maxn)) + 2, M = 1e9+7;
int dp[2][maxn];
int R, G;

int up(int x) {
    return x*(x+1)/2;
}

int solve(int L) {
    memset(dp,0,sizeof dp);
    dp[0][R] = 1;
    for (int i = 1; i <= L; i++) {
        bool all0 = true;
        for (int j = 0; j <= R; j++) {
            if (dp[0][j] == 0) continue;
            all0 = false;
            int r = j;
            int g = G - (up(i-1) - (R - r));
            if (g < 0) break;
            if (r-i >= 0) dp[1][r-i] = (dp[1][r-i] + dp[0][r]) % M;
            dp[1][r] = (dp[1][r] + dp[0][r]) % M;
        }
        if (all0) return 0;
        
        for (int j = 0; j <= R; j++) {
            dp[0][j] = dp[1][j];
            dp[1][j] = 0;
        }
        
    }
    
    int res = 0;
    for (int j = 0; j <= R; j++) {
        int r = j;
        int g = G - (up(L) - (R - r));
        if (g < 0) continue;
        res = (res + dp[0][j]) % M;
    }
    
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> R >> G;
    if (R > G) swap(R,G);
    int num = 0;
    for (;up(num) <= R+G; num++) {}
    num--;
    cout << solve(num) << '\n';
    

    return 0;
}
