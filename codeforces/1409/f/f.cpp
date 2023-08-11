#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 205;
int n, k;
string s, t;

int dp[maxn][maxn][maxn];
//[pos][# replacements left][# 1st letter]

void amax(int& a, int b) {
    a = max(a,b);
}

int f(int i, int r, int c) {
    int& res = dp[i][r][c];
    if (res != -1) return res;
    if (i == n) return res = 0;
    res = c*(s[i]==t[1])+f(i+1,r,c+(s[i]==t[0]));
    if (r > 0) 
        amax(res,c+f(i+1,r-1,c+(t[1]==t[0])));
    if (r > 0) 
        amax(res,c*(t[0]==t[1])+f(i+1,r-1,c+1));
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    cin >> s >> t;
    memset(dp,-1,sizeof dp);
    int ans = f(0,k,0);
    cout << ans << '\n';
}

/* Splits:
 * A: 1
 * B: 8
 * C: 10
 * D: 11
 * E: 19
 * F: 12
 */
