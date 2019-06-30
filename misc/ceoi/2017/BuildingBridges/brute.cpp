#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
typedef long double ld;
const ll INF = 1LL<<62;

//dp[i] = min_{1 <= j < i} (h[i]-h[j])^2 + sum(w[j+1]..w[i-1]) + dp[j]
// = (h[i]-h[j])^2 + pfx[i-1]-pfx[j]+dp[j]
// = h[i]^2 - 2h[i]*h[j] + h[j]^2 + pfx[i-1] - pfx[j] + dp[j]
// = (h[i]^2+pfx[i-1]) + (-2h[j])*h[i] + (dp[j]-pfx[j]) + h[j]^2
// =  (independent)    + (mx)          -      b 
// So each j has (m,b) = (-2h[j],dp[j]-pfx[j]+h[j]^2)
// Unfortunately, the h[i]'s and h[j]'s aren't monotonic, so we have implement a hull w/ dynamic 
// queries/insertions
//

int n;
ll h[maxn], w[maxn], pfx[maxn];
ll dp[maxn];
ll m[maxn], b[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        pfx[i] = w[i] + pfx[i-1];
    }
    m[1] = -2*h[1];
    b[1] = -pfx[1]+h[1]*h[1];
    for (int i = 2; i <= n; i++) {
        ll q = INF;
        for (int j = 1; j < i; j++) {
            q = min(q,h[i]*h[i]+pfx[i-1]+(-2*h[j])*h[i]+(dp[j]-pfx[j])+h[j]*h[j]);
        }
        dp[i] = q;
        if (i == n) {
            cout << q << '\n';
        }
    }
}

