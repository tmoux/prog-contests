#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxm = 21, INF = 1e9;
int n, m;
string s;
int cnt[21][21];

int dp[1<<maxm];

inline bool isSet(int mask, int j) {
    return mask & (1<<j);
}

//mask is set of numbers chosen already, 
int f(int mask) { 
    if (dp[mask] >= 0) return dp[mask];
    if ((mask + 1) == (1<<m)) {
        return dp[mask] = 0;
    }
    dp[mask] = INF;
    int angst = 0;
    for (int j = 0; j < m; j++) {
        if (!isSet(mask,j)) continue;
        for (int k = 0; k < m; k++) {
            if (isSet(mask,k)) continue;
            angst += cnt[j][k];
        }
    }
    for (int j = 0; j < m; j++) {
        dp[mask] = min(dp[mask],f(mask|(1<<j))+angst);
    }
    //printf("%d: %d, angst = %d\n",mask,dp[mask],angst);
    return dp[mask];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> s;
    for (int i = 0; i < n-1; i++) {
        if (s[i] == s[i+1]) continue;
        cnt[s[i]-'a'][s[i+1]-'a']++;
        cnt[s[i+1]-'a'][s[i]-'a']++;
    }
    memset(dp,-1,sizeof dp);
    int ans = f(0);
    cout << ans << '\n';
}

