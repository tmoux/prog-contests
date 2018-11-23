#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 205;
const ll NEG = -1e18;
int n, k, x;
int a[maxn];
ll dp[maxn][maxn][maxn]; //[pos][x][consec][left]

ll f(int i, int c, int l) {
    //cout << i << ' ' << c << ' ' << l << '\n';
    if (dp[i][c][l] != -1) return dp[i][c][l];
    if (i > n) return l == 0 ? 0 : NEG;
    ll aa = (c == 0 ? NEG : f(i+1,c-1,l));
    ll bb = (l == 0 ? NEG : f(i+1,k-1,l-1)+a[i]);
    return dp[i][c][l] = max(aa,bb);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> x;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memset(dp,-1,sizeof dp);
    ll ans = f(1,k-1,x);
    cout << (ans <= NEG/10 ? -1 : ans) << '\n';

    return 0;
}

