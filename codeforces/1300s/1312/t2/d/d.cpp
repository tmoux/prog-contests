#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
const int maxn = 2e5+5;
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
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
int n, m;
int fac[maxn], ifac[maxn];

int ch(int n, int k) {
    int res = fac[n];
    res = mult(res,ifac[k]);
    res = mult(res,ifac[n-k]);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = mult(fac[i-1],i);
        ifac[i] = modexp(fac[i],M-2);
    }
    if (n == 2) {
        cout << 0 << endl;
        return 0;
    }
    int ans = 0;
    for (int p = n-1; p <= m; p++) {
        int add = p-1;
        add = mult(add,ch(p-2,n-3));
        madd(ans,add);
    }
    ans = mult(ans,modexp(2,n-3));
    cout << ans << endl;
}
