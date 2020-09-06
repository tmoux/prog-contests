#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7, maxn = 1e5+5;
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
int choose(int n, int k) {
    assert(k <= n);
    int res = fac[n];
    res = mult(res,ifac[k]);
    res = mult(res,ifac[n-k]);
    return res;
}

void solve() {
    int N; cin >> N;
    map<int,int> mp;
    for (int i = 0; i < N; i++) {
        int ai; cin >> ai;
        ++mp[ai];
    }
    int x = mp.rbegin()->second;
    if (x&1) {
        cout << modexp(2,N) << '\n';
    }
    else {
        int bad = mult(choose(x,x/2),modexp(2,N-x));
        int tot = modexp(2,N);
        int ans = msub(tot,bad);
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = mult(fac[i-1],i);
        ifac[i] = inverse(fac[i]);
    }
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
