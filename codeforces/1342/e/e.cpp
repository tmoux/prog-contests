#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353, maxn = 2e5+5;
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
int fac[maxn], ifac[maxn];
int ch(int n, int r) {
    assert(r <= n);
    int res = fac[n];
    res = mult(res,ifac[r]);
    res = mult(res,ifac[n-r]);
    return res;
}
int n, k;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = mult(fac[i-1],i);
        ifac[i] = modexp(fac[i],M-2);
    }
    k = n-k;
    if (k <= 0) {
        cout << 0 << '\n';
    }
    else {
        int ans = 0;
        for (int i = 0; i <= k; i++) {
            int add = i % 2 == 0 ? 1 : M-1;
            add = mult(add,ch(k,i));
            add = mult(add,modexp(k-i,n));
            madd(ans,add);
            //cout << i << ": " << add << endl;
        }
        ans = mult(ans,ch(n,k));
        if (k < n) ans = mult(ans,2);
        cout << ans << '\n';
    }
}

