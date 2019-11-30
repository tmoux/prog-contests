#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 305;
int n, K, h[maxn];

ll dp[maxn][maxn][maxn];
ll INF = 1e18;
void amin(ll& a, ll b) {
    a = min(a,b);
}

ll f(int i, int j, int k) {
    //i=curr,j = index of current height, k = # modifications left available
    if (i == n+1) return h[j];
    ll& res = dp[i][j][k];
    if (res >= 0) return res;
    res = INF;
    if (h[i] > h[j]) {
        amin(res,f(i+1,i,k));
        if (k > 0) {
            amin(res,f(i+1,j,k-1));
        }
    }
    else if (h[i] < h[j]) {
        amin(res,h[j]-h[i]+f(i+1,i,k));
        if (k > 0) {
            amin(res,f(i+1,j,k-1));
        }
    }
    else {
        amin(res,f(i+1,j,k));
    }
    //printf("[%d][%d][%d]: %lld\n",i,j,k,res);
    return res;
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> K;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    memset(dp,-1,sizeof dp); 
    ll ans = f(1,0,K);
    cout << ans << '\n';
}

