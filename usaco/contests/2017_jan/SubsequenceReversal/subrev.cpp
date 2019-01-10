#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 55;
int N, a[maxn], dp[maxn][maxn][maxn][maxn]; //dp[l][r][left #][right #]

void amax(int& a, int b) {
    a = max(a,b);
}

int f(int l, int r, int ln, int rn) {
    int& res = dp[l][r][ln][rn];
    if (res != -1) return res;
    if (ln > rn) return -999999;
    if (l > r) return res = 0;
    if (l == r) return res = ln <= a[l] && a[l] <= rn ? 1 : 0;   
    //first consider not switching at all
    res = 0;
    amax(res,f(l+1,r,ln,rn));
    amax(res,f(l,r-1,ln,rn));
    if (ln <= a[l]) amax(res, 1 + f(l+1,r,a[l],rn));
    if (a[r] <= rn) amax(res, 1 + f(l,r-1,ln,a[r]));
    //now consider switching a[l] and a[r]
    if (ln <= a[r] && a[l] <= rn) amax(res, 2 + f(l+1,r-1,a[r],a[l]));
    if (ln <= a[r]) amax(res, 1 + f(l+1,r-1,a[r],rn));
    if (a[l] <= rn) amax(res, 1 + f(l+1,r-1,ln,a[l]));
    return res;
}

int main()
{
    freopen("subrev.in","r",stdin); freopen("subrev.out","w",stdout);
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    memset(dp,-1,sizeof(dp));
    int ans = f(1,N,0,51);
    cout << ans << '\n';


    return 0;
}

