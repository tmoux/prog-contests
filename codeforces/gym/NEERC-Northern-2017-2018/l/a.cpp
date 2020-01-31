#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n;

ll modexp(ll a, ll b) {
    ll r = 1;
    while (b--) {
        ll res = r*a;
        if (r != res/a) return 2e18;
        else r = res;
    }
    return r;
}

ll nth_root(ll n, int i) {
    ll x = (ll)pow(n,1.0/i);
    for (ll j = max(1LL,x-20); j <= x+20; j++) {
        if (modexp(j+1,i) > n) {
            return j;
        }
    }
    assert(false);
}

ll multiply(vector<ll> mult) {
    ll r = 1;
    for (ll i: mult) {
        ll res = r*i;
        if (r != res/i) return 2e18;
        else r = res;
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("little.in","r",stdin); freopen("little.out","w",stdout);
    cin >> n;
    ll cp = n;
    while (cp % 2 == 0) cp /= 2;
    if (cp == 1) {
        cout << -1 << '\n';
        return 0;
    }
    vector<vector<ll>> ans;
    for (int i = 1; i <= 60; i++) {
        ll rt = nth_root(n,i);
        //cout << i << ": " << rt << endl;
        vector<ll> mult = vector<ll>(i,rt);
        if (multiply(mult) == n) {
            ans.push_back(mult);
            continue;
        }
        for (int j = 0; j < i; j++) {
            mult[j] = rt+1;
            ll m = multiply(mult);
            if (m == n) {
                ans.push_back(mult);
                break;
            }
            else if (m > n) break;
        }
    }
    //output
    cout << ans.size() << endl;
    for (auto v: ans) {
        cout << v.size() << ' ';
        for (int i: v) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
