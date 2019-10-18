#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
const int maxn = 2005;
int N, T, Q;
int t[maxn];

void madd(int& a, int b) {
    a += b;
    if (a > M) a -= M;
}
int dp[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> T >> Q;
    for (int i = 1; i <= N; i++) {
        cin >> t[i];
    }
    while (Q--) {
        int a, b, q; cin >> a >> b >> q;
        for (int i = 0; i <= N+1; i++) {
            for (int j = 0; j <= T; j++) {
                dp[i][j] = 0;
            }
        }
        dp[1][0] = 1;
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j <= T; j++) {
                if (i == a || i == b) {
                    if (j+t[i] <= T) 
                        dp[i+1][j+t[i]] = dp[i][j];
                }
                else {
                    madd(dp[i+1][j],dp[i][j]);
                    if (j+t[i] <= T) 
                        madd(dp[i+1][j+t[i]],dp[i][j]);
                }
            }
        }
        int sum = 0;
        for (int i = 0; i <= q; i++) {
            //cout << i << ": " << dp[N+1][i] << '\n';
            madd(sum,dp[N+1][i]);
        }
        cout << sum << '\n';
    }
}

