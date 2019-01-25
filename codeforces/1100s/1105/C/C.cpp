#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, M = 1e9+7;
int n, l, r;
int c[3];
ll dp[maxn][3];
ll mult(ll a, ll b) {
    return (a*b) % M;
}
void madd(ll& a, ll b) {
    a = (a+b) % M;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> l >> r;
    for (int i = 0; i < 3; i++) {
        int rr = r;
        for (; rr >= max(l,r-2); rr--) {
            if (rr % 3 == i) break;                    
        }
        int ll = l;
        for (; ll <= min(r,l+2); ll++) {
            if (ll % 3 == i) break;
        }
        if (ll % 3 != i || rr % 3 != i) continue;
        c[i] = (rr-ll)/3 + 1; 
        //cout << i << ": " << c[i] << '\n';
    }
    for (int i = 0; i < 3; i++) {
        dp[1][i] = c[i];
        //cout << i << ": " << dp[1][i] << '\n';
    }
    for (int i = 2; i <= n; i++) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                madd(dp[i][k],mult(dp[i-1][j],c[(k-j+3)%3]));
            }
            //printf("dp[%d][%d]: %d\n",i,k,dp[i][k]);
        }
    }
    cout << dp[n][0] << '\n';

    return 0;
}

