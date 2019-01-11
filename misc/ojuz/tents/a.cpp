#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3005, M = 1e9+7;
ll dp[maxn][maxn];
int madd(int a, int b) {
    a += b;
    while (a > M) a -= M;
    return a;
}

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

ll ch2(int a) {
    return ((1LL*a*(a-1))/2) % M;
}

ll f(int i, int j) {
    if (i < 0 || j < 0) return 0;
    if (i == 0 || j == 0) return 1;
    ll& res = dp[i][j];
    if (res != -1) return res;
    res = 0;
    res = madd(res,mult(ch2(j),f(i-1,j-2)));
    res = madd(res,mult(mult(4,j),f(i-1,j-1)));
    res = madd(res,mult(mult(j,i-1),f(i-2,j-1)));
    res = madd(res,f(i-1,j));
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int H, W; cin >> H >> W;
    memset(dp,-1,sizeof dp);
    cout << (f(H,W)+M-1) % M << '\n';

    return 0;
}

