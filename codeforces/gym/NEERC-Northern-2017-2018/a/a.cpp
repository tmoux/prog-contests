#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int dp[maxn];

int v[8] = {0,0,1,7,4,5,9,8};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("auxiliary.in","r",stdin); freopen("auxiliary.out","w",stdout);
    int n; cin >> n;
    memset(dp,-1,sizeof dp);
    dp[0] = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= 7; j++) {
            if (i-j >= 0 && dp[i-j] >= 0) {
                dp[i] = max(dp[i],v[j]+dp[i-j]);
                //cout << i << ": " << v[j] << ' ' << dp[i-j] << '\n';
            }
        }
    }
    cout << dp[n] << '\n';
}

