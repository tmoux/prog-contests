#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
const int maxn = 5005;
int dp[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s, t; cin >> s >> t;
    for (int i = (int)s.size()-1; i >= 0; i--) {
        for (int j = (int)t.size()-1; j >= 0; j--) {
            dp[i][j] = dp[i][j+1];
            if (s[i] == t[j]) {
                madd(dp[i][j],dp[i+1][j+1]);
                madd(dp[i][j],1);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        madd(ans,dp[i][0]);
    }
    cout << ans << '\n';
}
