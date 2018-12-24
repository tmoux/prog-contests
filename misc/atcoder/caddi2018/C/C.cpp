#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<ll,int> facs;
void factor(ll i) {
    for (ll j = 2; j*j <= i; j++) {
        if (i % j == 0) {
            while (i % j == 0) {
                i /= j;
                facs[j]++;
            }
            factor(i);
            return;
        }
    }
    if (i > 1) {
        facs[i]++;
    }
}

ll expo(ll a, ll n) {
    ll res = 1;
    for (int i = 0; i < n; i++) {
        res *= a;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll N, P; cin >> N >> P;
    factor(P);
    ll ans = 1;
    for (auto p: facs) {
        ll r = p.second / N;        
        ans *= expo(p.first,r);
    }
    cout << ans << '\n';


    return 0;
}

