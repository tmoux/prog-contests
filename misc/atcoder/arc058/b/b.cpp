#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7, maxn = 1e5+5;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}
int fac[2*maxn], ifac[2*maxn];
int H, W, A, B;

int calc(int a, int b, int c, int d) {
    int n = c-a;
    int m = d-b;
    int res = fac[n+m];
    res = mult(res,ifac[n]);
    res = mult(res,ifac[m]);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < 2*maxn; i++) {
        fac[i] = mult(i,fac[i-1]);
        ifac[i] = inverse(fac[i]);
    }
    cin >> H >> W >> A >> B;
    int i = H-A-1;
    int j = B;
    int ans = 0;
    while (i >= 0 && j < W) {
        madd(ans,mult(calc(0,0,i,j),calc(i,j,H-1,W-1)));
        i--; j++;
    }
    cout << ans << '\n';
}

