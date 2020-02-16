#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
string s;

int dp[maxn];
int x[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = s[i]-'a'+1; j < 26; j++) {
            dp[i] = max(dp[i],x[j]+1);
        }
        x[s[i]-'a'] = max(x[s[i]-'a'],dp[i]);
    }
    int ans = 0;
    for (int i = 0; i < 26; i++) ans = max(ans,x[i]);
    cout << ans << '\n';
    for (int i = 0; i < n; i++) {
        cout << dp[i] << ' ';
    }
    cout << '\n';
}
