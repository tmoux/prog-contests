#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1e9+7;
int mult(int& a, int b) {
    return a = (1LL*a*b) % M;
}
int madd(int& a, int b) {
    return a = (a+b) % M;
}
int msub(int& a, int b) {
    return a = (a-b+M) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) mult(res,a);
        mult(a,a);
        b >>= 1;
    }
    return res;
}
int inverse(int a) {
    return modexp(a,M-2);
}

int mu[maxn];

void mobius_sieve(int m) {
    mu[1] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 2*i; j <= m; j += i) {
            mu[j] -= mu[i];
        }
    }
    //for mod = 1e9+7
    for (int i = 1; i <= m; i++) {
        if (mu[i] == -1) mu[i] = M-1;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int m; cin >> m;
    mobius_sieve(m);
    int ans = 1;
    for (int i = 2; i <= m; i++) {
        int f = m/i;
        msub(ans,mult(mu[i],mult(f,inverse(m-f))));
    }
    cout << ans << '\n';
}

