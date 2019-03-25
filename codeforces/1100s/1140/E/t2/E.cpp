#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//I don't want to do this problem anymore
const int maxn = 2e5+5, M = 998244353;
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int madd(int a, int b) {
    return (a+b) % M;
}
int modexp(int a, int b) {
    int r = 1;
    while (b) {
        if (b&1) r = mult(r,a);
        a = mult(a,a);
        b >>= 1;
    }
    return r;
}
int sqr(int x) {
    return (1LL*x*x) % M;
}
int inverse(int x) {
    return modexp(x,M-2);
}
int n, k, a[maxn];
int d[maxn];
int N;
ll dp[2][maxn]; //dp[0][i] = # non-ones, dp[1][i] = # ones
ll cntSame[maxn], cntDiff[maxn];

bool val(int x) {
    return 1 <= x;
}

ll solve(int l, int r) {
    int len = r - l - 1;
    if (l == 0 && r == N + 1) {
        return mult(k,modexp(k-1,len-1));
    }
    if (l == 0 || r == N + 1) {
        return modexp(k-1,len);
    }
    return d[l] == d[r] ? cntSame[len] : cntDiff[len];
}

ll getdp() {
    memset(dp,0,sizeof(dp));
    int res = 1;
    int prev = 0;
    for (int i = 1; i <= N+1; i++) {
        if (d[i] == -1) continue;
        res = mult(res,solve(prev,i));
        //cout << prev << ' ' << i << ": " << solve(prev,i) << '\n';
        //cout << prev << ' ' << i << '\n';
        prev = i;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    //fill in dp
    cntSame[0] = 0;
    cntDiff[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (i&1) {
            cntSame[i] = madd(sqr(cntSame[i/2]),mult(k-1,sqr(cntDiff[i/2])));
            cntDiff[i] = madd(mult(2,mult(cntSame[i/2],cntDiff[i/2])),mult(k-2,sqr(cntDiff[i/2])));
        }
        else {
            cntSame[i] = mult(k-1,cntDiff[i-1]);
            cntDiff[i] = madd(cntSame[i-1],mult(k-2,cntDiff[i-1]));
        }
    }
    ll ans = 1;
    int pt = 1;
    for (int i = 1; i <= n; i+=2) {
        d[pt++] = a[i];
    }
    N = pt-1;    
    ans = mult(ans,getdp());
    //cout << ans << '\n';
    pt = 1;
    memset(d,0,sizeof(d));
    for (int i = 2; i <= n; i+=2) {
        d[pt++] = a[i];
    }
    N = pt-1;
    ans = mult(ans,getdp());
    cout << ans << '\n';
}

