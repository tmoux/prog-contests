#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105, maxk = 1e5+5;
const int M = 1e9+7;
int N, K, a[maxn];

void madd(int& a, int b) {
    a += b;
    while (a > M) a -= M;
}

int dp[maxn][maxk];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    for (int j = 0; j <= a[1]; j++) {
        dp[1][j] = 1;    
    }
    for (int i = 2; i <= N; i++) {
        for (int k = 1; k <= K; k++) {
            madd(dp[i-1][k],dp[i-1][k-1]);
        }
        for (int k = 0; k <= K; k++) {
            dp[i][k] = dp[i-1][k];
            if (k-min(k,a[i]) > 0) dp[i][k] = (dp[i][k] - dp[i-1][k-min(k,a[i])-1] + M) % M;
        }
    }
    int ans = dp[N][K];
    cout << ans << '\n';

    return 0;
}

