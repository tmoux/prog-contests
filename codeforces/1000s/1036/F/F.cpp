#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

set<ll> inl;
vector<ll> sorted;

bool isSquare(ll x) {
    ll a = (ll)(sqrt((double)x));
    return (a*a == x || (a+1)*(a+1) == x);
}

ll sqflr(ll x) {
    ll a = (ll)(sqrt((double)x)) + 2;
    while (a*a > x) a--;
    return a;
}

ll ex(ll a, int n) {
    ll res = 1;
    for (int i = 0; i < n; i++) {
        res *= a;
        if (res < 0 || res > 4e18+5) return -1;
    }
    return res;
}

ll solve(ll ni) {
    ll sq = sqflr(ni);
    auto it = upper_bound(sorted.begin(),sorted.end(),ni);
    ll inelegant = (ll)(distance(sorted.begin(),it)) + sq;
    return ni - inelegant;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int n = 3; n <= 64; n+=2) {
        for (int i = 2; ; i++) {
            ll f = ex(i,n);
            if (f <= -1) break;
            if (!isSquare(i) && f > 0) inl.insert(f);
        }
    }
    int t; cin >> t;
    for (ll i: inl) if (i > 0) sorted.push_back(i);
    while (t--) {
        ll ni; cin >> ni;
        cout << solve(ni) << '\n';
    }
    

    return 0;
}
