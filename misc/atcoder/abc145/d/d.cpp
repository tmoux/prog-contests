#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6, M = 1e9+7;
int fac[maxn], ifac[maxn];
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

int comb(int n, int r) {
    return mult(fac[n],mult(ifac[r],ifac[n-r]));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x, y; cin >> x >> y;
    fac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = mult(fac[i-1],i);
    }
    for (int i = 0; i < maxn; i++) {
        ifac[i] = modexp(fac[i],M-2);
    }
    if ((2*x-y) < 0 || (2*x-y) % 3 != 0) {
        cout << 0 << '\n';
    }
    else {
        int b = (2*x-y)/3;
        int a = x-2*b;
        if (a >= 0 && b >= 0) {
            cout << comb(a+b,a) << '\n';
        }
        else {
            cout << 0 << '\n';
        }
    }
}

