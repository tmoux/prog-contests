#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = 1e9+7;
ll modexp(ll x, ll n) {
    if (n == 0) return 1;
    if (n == 1) return x%M;
    if (n%2==0) return modexp((x*x)%M,n/2);
    return (x*modexp((x*x)%M,n/2))%M;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    const int maxn = 1e5+5;
    int n, q; cin >> n >> q;
    vector<int> pre(n+1);
    string s; cin >> s;
    for (int i = 1; i <= n; i++) {
        pre[i] = s[i-1] - '0';
        pre[i] += pre[i-1];
    }
    while (q--) {
        int l, r; cin >> l >> r;
        int a = pre[r] - pre[l-1];
        int b = (r-l+1) - a;
        ll ans = (modexp(2,a+b) - modexp(2,b) + M) % M;
        cout << ans << '\n';
    }

    return 0;
}

