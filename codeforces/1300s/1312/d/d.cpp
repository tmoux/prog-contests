#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, M = 998244353;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}
int n, m;
int fac[maxn], ifac[maxn], ex2[maxn];

int comb(int n, int k) {
    if (k > n) return 0;
    int res = fac[n];
    res = mult(res,ifac[k]);
    res = mult(res,ifac[n-k]);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    if (n == 2) {
        cout << 0 << endl;
        return 0;
    }
    fac[0] = ifac[0] = ex2[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = mult(fac[i-1],i);
        ifac[i] = inverse(fac[i]);
        ex2[i] = mult(ex2[i-1],2);
    }
    int ans = 0;
    for (int p = n-1; p <= m; p++) {
        int add = p-1;
        add = mult(add,comb(p-2,n-3));
        add = mult(add,ex2[n-3]);
        madd(ans,add);
    }
    cout << ans << '\n';
}
