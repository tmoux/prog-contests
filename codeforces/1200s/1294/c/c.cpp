#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n;

map<ll,ll> fac;

void factor(ll x) {
    for (ll i = 2; i*i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                x /= i;
                fac[i]++;
            }
            factor(x);
            return;
        }
    }
    if (x > 1) fac[x]++;
}

ll mexp(ll a, ll b) {
    ll r = 1;
    while (b--) {
        r *= a;
    }
    return r;
}

void solve(ll n) {
    fac.clear();
    factor(n);
    vector<pair<ll,ll>> v;
    for (auto p: fac) {
        v.push_back(p);
    }
    ll a = 0, b = 0, c = 0;
    if (v.size() >= 3) {
        a = mexp(v[0].first,v[0].second);
        b = mexp(v[1].first,v[1].second);
        c = n/(a*b);
    }
    else if (v.size() == 2) {
        sort(v.begin(),v.end(),[](auto a, auto b) {
                return a.second > b.second;
                });
        if (v[0].second >= 3) {
            a = mexp(v[0].first,1);
            b = mexp(v[0].first,2);
            c = n/(a*b);
        }
        else if (v[0].second == 2 && v[1].second == 2) {
            a = v[0].first;
            b = v[1].first;
            c = n/(a*b);
        }
    }
    else {
        assert(v.size() == 1);
        if (v[0].second >= 6) {
            a = mexp(v[0].first,1);
            b = mexp(v[0].first,2);
            c = n/(a*b);
        }
    }
    /*
    for (auto p: v) {
        cout << p.first << ' ' << p.second << '\n';
    }
    */
    if (a*b*c == n) {
        cout << "YES\n";
        assert(a != b && b != c && a != c);
        cout << a << ' ' << b << ' ' << c << '\n';
    }
    else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        solve(n);
    }
}

