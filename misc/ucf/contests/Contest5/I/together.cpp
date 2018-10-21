#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 505;
const ll INF = 1e18;
int n, pop[maxn];
ll pre[maxn], cost[maxn];
ll dp[maxn][maxn];

ll sum(int l, int r) {
    return pre[r] - pre[l-1];
}

ll f(int l, int r) {
    if (dp[l][r] >= 0) return dp[l][r];
    if (l == r) return 0;
    dp[l][r] = INF;
    for (int i = l; i < r; i++) {
        //cout << "I=" << i << '\n';
        //split point
        dp[l][r] = min(dp[l][r],f(l,i)+f(i+1,r)+(ll)min(cost[i],cost[i+1])*sum(l,r));
    }
    return dp[l][r];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pop[i];
        pre[i] = pre[i-1] + pop[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
    }
    memset(dp,-1,sizeof(dp));
    ll ans = f(1,n);
    //cout << min(cost[1],cost[2])*sum(1,2) << '\n';
    cout << ans;
    
    return 0;
}
	

