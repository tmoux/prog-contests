#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll maxn = 3e5+5;
ll n, A[2][maxn];
ll presum[2][maxn], fwd[2][maxn], backward[2][maxn];

ll getsum(ll l, ll r, ll j) {
    if (l == 0) return presum[j][r];
    else return presum[j][r] - presum[j][l-1];
}

ll calc(ll j, ll i, ll x) {
    ll delta = x - i;
    if (j == 0) {
        return fwd[j][i] + delta*getsum(i,n-1,j) + fwd[j^1][i] + delta*getsum(i,n-1,j^1);
    }
    return backward[j][i] + delta*getsum(i,n-1,j) + backward[j^1][i] + delta*getsum(i,n-1,j^1);
}

ll dp[2][maxn];

ll f(ll j, ll i) {
    if (dp[j][i] >= 0) return dp[j][i];
    ll x = 2*i;
    if (i == n - 1) return dp[j][i] = 1LL*x*A[j][i] + 1LL*(x+1)*A[j^1][i];
    return dp[j][i] = max(calc(j,i,x),1LL*x*A[j][i]+1LL*(x+1)*A[j^1][i] + f(j^1,i+1)); 
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (ll i = 0; i < 2; i++) {
        for (ll j = 0; j < n; j++) {
            cin >> A[i][j];
            presum[i][j] = A[i][j];
            if (j != 0) presum[i][j] += presum[i][j-1];
        }
    }
    for (ll i = n - 1; i >= 0; i--) {
        for (ll j = 0; j < 2; j++) {
            if (j == 0) {
                if (i == n - 1) {
                    fwd[j][i] = 1LL*(n-1)*A[j][i];
                }
                else {
                    fwd[j][i] = fwd[j][i+1] + i*A[j][i];
                }
            }
            else {
                if (i == n - 1) {
                    fwd[j][i] = 1LL*n*A[j][i];
                }
                else {
                    fwd[j][i] = fwd[j][i+1] + (n+(n-i)-1)*A[j][i];
                }
            }
        }
    }
    for (ll i = n - 1; i >= 0; i--) {
        for (ll j = 0; j < 2; j++) {
            if (j == 1) {
                if (i == n - 1) {
                    backward[j][i] = 1LL*(n-1)*A[j][i];
                }
                else {
                    backward[j][i] = backward[j][i+1] + i*A[j][i];
                }
            }
            else {
                if (i == n - 1) {
                    backward[j][i] = 1LL*n*A[j][i];
                }
                else {
                    backward[j][i] = backward[j][i+1] + (n+(n-i)-1)*A[j][i];
                }
            }
        }
    }

    memset(dp,-1,sizeof(dp));
    ll ans = f(0,0);
    cout << ans << '\n';
    /*
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cout << backward[i][j] << ' ';
        }
        cout << '\n';
    }
    */

    return 0;
}
	

