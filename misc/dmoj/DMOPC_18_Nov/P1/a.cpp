#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, NANA = -2e9, INF = -1e9;
int N, a[maxn], b[maxn];
int dp[maxn][3];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < N; i++) cin >> b[i];
    for (int i = N - 1; i >= 0; i--) {
        for (int k = 0; k <= 2; k++) {
            if (k == 2) {
                dp[i][k] = b[i] + dp[i+1][0];
            }
            else {
                dp[i][k] = max(b[i]+dp[i+1][0],a[i]+dp[i+1][k+1]);
            }
        }
    }
    int ans = max(dp[0][0],max(dp[0][1],dp[0][2]));
    cout << ans << '\n';

    return 0;
}

