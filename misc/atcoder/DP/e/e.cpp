#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105, maxv = 1005;
const ll INF = 1e18;
int N, W;
int weight[maxn], val[maxn];
ll dp[maxn][maxv*maxn];

ll f(int i, int v) { //dp for min cost to obtain this value
    if (v < 0) return INF;
    if (i == N) {
        return v == 0 ? 0 : INF;
    }
    if (dp[i][v] != -1) return dp[i][v];
    return dp[i][v] = min(weight[i] + f(i+1,v-val[i]),f(i+1,v));            
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> W;
    for (int i = 0; i < N; i++) {
        cin >> weight[i] >> val[i];
    }
    memset(dp,-1,sizeof dp);
    int ans = 0;
    for (int v = 1; v <= N*1000; v++) {
        if (f(0,v) <= W) ans = v;
    }
    cout << ans << '\n';

    return 0;
}

