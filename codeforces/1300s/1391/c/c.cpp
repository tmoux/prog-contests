#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7, maxn = 1e6+6;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int msub(int a, int b) {
    madd(a,M-b);
    return a;
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
int fac[maxn], ifac[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = mult(i,fac[i-1]);
        ifac[i] = inverse(fac[i]);
    }
    int n; cin >> n;
    int tot = fac[n];
    tot = msub(tot,modexp(2,n-1));
    cout << tot << '\n';
}
