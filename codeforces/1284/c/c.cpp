#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;

int n, M;

void madd(int& a, int& b) {
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
int fac[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> M;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = mult(fac[i-1],i);
    }
    ll ans = 0;
    for (int l = 1; l <= n; l++) {
        int add = n-l+1;
        add = mult(add,add);
        add = mult(add,fac[l]);
        add = mult(add,fac[n-l]);
        ans = (ans+add) % M;
    }
    cout << ans << '\n';
}

