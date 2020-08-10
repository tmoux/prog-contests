#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int N, K;
int f[maxn];
int dp[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> N >> K;
        for (int i = 1; i <= N; i++) {
            cin >> f[i];
        }
        dp[0] = 0;
        for (int i = 1; i <= N; i++) {
            dp[i] = 2e9;
            map<int,int> mp;
            int cur = 0;
            for (int j = i; j >= 1; j--) {
                ++mp[f[j]];
                if (mp[f[j]] == 2) cur += 2;
                else if (mp[f[j]] > 2) cur++;
                dp[i] = min(dp[i],dp[j-1]+K+cur);
            }
        }
        cout << dp[N] << '\n';
    }
}
