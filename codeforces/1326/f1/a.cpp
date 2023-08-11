#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int pc(int x) {
    return __builtin_popcount(x);
}

const int maxn = 14;
int n, g[maxn][maxn];
vector<ll> dp[1<<14][14];
vector<int> masks[15];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c; cin >> c;
            g[i][j] = c-'0';
        }
    }
    for (int i = 0; i < (1<<n); i++) {
        masks[pc(i)].push_back(i);
    }
    for (int j = 0; j < n; j++) {
        dp[1<<j][j].push_back(1);
    }
    for (int i = 1; i < n; i++) {
        for (int m: masks[i-1]) {
            for (int j = 0; j < n; j++) {
                dp[m][j].clear();
            }
        }
        for (int m: masks[i+1]) {
            for (int j = 0; j < n; j++) {
                dp[m][j].resize(1<<i);
            }
        }
        for (int m: masks[i]) {
            for (int j = 0; j < n; j++) {
                if (!(m & (1<<j))) continue;
                for (int s = 0; s < dp[m][j].size(); s++) {
                    for (int k = 0; k < n; k++) {
                        if (m & (1<<k)) continue;
                        int add = g[j][k];
                        dp[m|(1<<k)][k][s|(add<<(i-1))] += dp[m][j][s];
                    }
                }
            }
        }
    }
    for (int s = 0; s < (1<<(n-1)); s++) {
        ll ans = 0;
        for (int j = 0; j < n; j++) {
            ans += dp[(1<<n)-1][j][s];
        }
        cout << ans << ' ';
    }
    cout << '\n';
}
