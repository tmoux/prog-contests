#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 13;
int N, M, a[1005], mask[1005];
ll dp[1<<maxn][1005];
const ll INF = 1e15;

ll f(int msk, int i) {
    if (dp[msk][i] != -1) return dp[msk][i];
    if (i == M) {
        //cout << msk << ": " << ((msk+1) == (1<<N)) << '\n';
        dp[msk][i] = ((msk+1) == (1<<N)) ? 0 : INF;
        //printf("[%d][%d]: %lld\n",msk,i,dp[msk][i]);
        return dp[msk][i];
    }
    dp[msk][i] = INF;
    dp[msk][i] = min(dp[msk][i],f(msk,i+1));
    dp[msk][i] = min(dp[msk][i],f(msk|mask[i],i+1)+a[i]);
    //printf("[%d][%d]: %lld\n",msk,i+1,f(msk,i+1));
    //printf("[%d][%d]: %lld\n",msk|mask[i],i+1,f(msk|mask[i],i+1)+a[i]);
    return dp[msk][i];
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> a[i];
        int bi; cin >> bi;
        while (bi--) {
            int ci; cin >> ci;
            ci--;
            mask[i] |= 1<<ci;
        }
        //cout << i << ": " << mask[i] << '\n';
    }
    memset(dp,-1,sizeof dp);
    ll ans = f(0,0);
    cout << (ans < INF ? ans : -1) << '\n';
}
