#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105, maxw = 1e5+5;
int N, W;
int weight[maxn], val[maxn];

ll dp[maxn][maxw];
ll f(int i, int w) {
    if (w > W) return -999999999;
    if (i == N) return dp[i][w] = 0;
    if (dp[i][w] != -1) return dp[i][w];
    return dp[i][w] = max(f(i+1,w),val[i] + f(i+1,w+weight[i]));    
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> W;
    for (int i = 0; i < N; i++) {
        cin >> weight[i] >> val[i];
    }
    memset(dp,-1,sizeof dp);
    ll ans = f(0,0);
    cout << ans << '\n'; 

    return 0;
}

