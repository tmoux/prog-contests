#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 22, NEG = -999999999;
int N, H, height[maxn], weight[maxn], strength[maxn];
map<int,int> dp[1<<maxn];

int f(int mask, int excess) {
	if (dp[mask].count(excess)) return dp[mask][excess];

}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("guard.in","r",stdin);
    //freopen("guard.out","w",stdout);
    cin >> N >> H;
    for (int i = 0; i < N; i++) {
    	cin >> height[i] >> weight[i] >> strength[i];
    }
    memset(dp,-1,sizeof dp);
    int maxans = NEG;
    for (int i = 0; i < N; i++) {
    	maxans = max(maxans,f(1<<i,strength[i]));
    }



    return 0;
}