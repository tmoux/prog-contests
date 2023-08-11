#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, k;
ll a, b;
ll dist(ll x) {
    //returns distance to nearest thing
    return min((x-1) % k,k-((x-1)%k));
}

ll calc(ll x) {
    return 1LL*n*k/__gcd(1LL*n*k,x);
}

ll f(ll x) {
    return x == 0 ? k : x;
}

pair<ll,ll> g(ll t) {
    ll l0 = f(((k + 1 + b) - t + k) % k);
    ll l1 = f(((k + 1 - b) - t + k) % k);
    //cout << l0 << ' ' << l1 << '\n';
    pair<ll,ll> r = {1e18,-1e18};
    for (ll l = l0; l <= 1LL*n*k; l += k) {
        r.first = min(r.first,calc(l));
        r.second = max(r.second,calc(l));
    }
    for (ll l = l1; l <= 1LL*n*k; l += k) {
        r.first = min(r.first,calc(l));
        r.second = max(r.second,calc(l));
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    cin >> a >> b;
    ll t1 = a + 1;
    ll t2 = k + 1 - a;
    auto p1 = g(t1);
    auto p2 = g(t2);
    cout << min(p1.first,p2.first) << ' ' << max(p1.second,p2.second) << '\n';
}

