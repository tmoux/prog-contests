#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, cost[3][maxn];
int dp[3][maxn];

int f(int t, int i) {
    if (i == N) return 0;
    if (dp[t][i] != -1) return dp[t][i];
    for (int j = 0; j < 3; j++) {
        if (t == j) continue;
        dp[t][i] = max(dp[t][i],f(j,i+1) + cost[j][i]);
    }
    return dp[t][i];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> cost[j][i];
        }
    }
    memset(dp,-1,sizeof(dp));
    int ans = max(max(f(0,0),f(1,0)),f(2,0));
    cout << ans << '\n';

    return 0;
}

