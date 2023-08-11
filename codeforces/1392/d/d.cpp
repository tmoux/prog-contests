#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, INF = 2e9;
int n;
char a[maxn];
int dp[maxn];
int diff(int i, string s) {
    int res = 0;
    for (int j = 0; j < s.size(); j++) {
        res += a[i+j] != s[j];        
    }
    return res;
}
void solve() {
    cin >> n;
    string s; cin >> s;
    int ans = INF;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < n; i++) {
            a[i] = s[(i+j)%n];
        }
        dp[0] = INF;
        dp[1] = diff(0,"RL");
        dp[2] = min(diff(0,"RLL"),diff(0,"RRL"));
        if (n > 3) {
            dp[3] = min(diff(0,"RRLL"),dp[1]+diff(2,"RL"));
            for (int i = 4; i < n; i++) {
                dp[i] = INF;
                dp[i] = min(dp[i],dp[i-2]+diff(i-1,"RL"));
                dp[i] = min(dp[i],dp[i-3]+diff(i-2,"RLL"));
                dp[i] = min(dp[i],dp[i-3]+diff(i-2,"RRL"));
                dp[i] = min(dp[i],dp[i-4]+diff(i-3,"RRLL"));
            }
        }
        //cout << j << ": " << dp[n-1] << endl;
        ans = min(ans,dp[n-1]);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
