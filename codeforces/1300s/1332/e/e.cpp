#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int msub(int a, int b) {
    madd(a,M-b);
    return a;
}
int modexp(int a, ll b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1LL;
    }
    return res;
}
int inverse(int x) {
    return modexp(x,M-2);
}

int countEven(int x) {
    return x/2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m, L, R; cin >> n >> m >> L >> R;
    ll nm = 1LL*n*m;
    if (nm&1LL) {
        int ans = modexp(R-L+1,nm);
        cout << ans << '\n';
        return 0;
    }
    int a = countEven(R) - countEven(L-1);
    int b = (R-L+1) - a;
    int ans = 0;
    auto f = [](int a, int b, ll nm) {
        int res = 0;
        madd(res,modexp((a+b)%M,nm));
        madd(res,modexp(msub(a,b),nm));
        res = mult(res,inverse(2));
        return res;
    };
    madd(ans,f(a,b,nm));
    cout << ans << '\n';
}

