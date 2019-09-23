#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e7+7;
int mu[maxn];
//O(n log n) sieve seems to be fast enough in most cases

void mobius_sieve(int m) {
    mu[1] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 2*i; j <= m; j += i) {
            mu[j] -= mu[i];
        }
    }
}

ll solve(int n, int m) {
    ll ret = 0;
    for (int i = 1; i <= min(n,m); i++) {
        ret += mu[i] * (ll)(n/i) * (m/i);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b, c, d; cin >> a >> b >> c >> d;
    mobius_sieve(max(b,d));
    ll ans = solve(b,d) - solve(a-1,d) - solve(b,c-1) + solve(a-1,c-1);
    cout << ans << '\n';
}

