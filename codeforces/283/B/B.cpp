#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
const ll INF = 1e18;
int n, A[maxn];
ll dp[2][maxn];
bool seen[2][maxn];
//dp[0] is decrease mode, dp[1] is increasing
ll f(int k, int i) {
	if (k == 1 && i == 1) return INF;
	if (i <= 1 || i > n) return 0LL;
	if (dp[k][i] >= 0) return dp[k][i];
	if (seen[k][i]) return dp[k][i] = INF;
	seen[k][i] = true;
	if (k == 0) {
		return dp[k][i] = A[i] + f(1,i-A[i]);
	}
	else return dp[k][i] = A[i] + f(0,i+A[i]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    memset(dp,-1,sizeof(dp));
    cin >> n;
    for (int i = 2; i <= n; i++) {
    	cin >> A[i];
    }
    for (int i = 1; i < n; i++) {
   		ll ans = f(0,1+i) + i;
   		cout << (ans >= INF ? -1 : ans) << '\n';
    }


    return 0;
}