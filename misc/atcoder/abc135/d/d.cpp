#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1e9+7;
string s;
int n;
int dp[13][maxn];

int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = (1LL*res*a) % 13;
        a = (1LL*a*a) % 13;
        b >>= 1;
    }
    return res;
}

int f(int mod, int i) {
    if (dp[mod][i] >= 0) return dp[mod][i];
    if (i == n) return dp[mod][i] = mod == 5 ? 1 : 0;
    if (s[i] != '?') {
        int d = s[i]-'0';
        int m = (1LL*d*modexp(10,i)) % 13;
        return dp[mod][i] = f((mod+m)%13,i+1);
    }
    else {
        dp[mod][i] = 0;
        for (int d = 0; d < 10; d++) {
            int m = (1LL*d*modexp(10,i)) % 13;
            dp[mod][i] = (dp[mod][i] + f((mod+m)%13,i+1)) % M;        
        }
        //cout << mod << ' ' << i << ": " << dp[mod][i] << '\n';
        return dp[mod][i];
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;
    n = s.size();
    reverse(s.begin(),s.end());
    memset(dp,-1,sizeof dp);
    int ans = f(0,0);
    cout << ans << '\n';
}

