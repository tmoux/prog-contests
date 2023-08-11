#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, p; cin >> n >> p;
    for (ll x = 1; x <= 100000; x++) {
        ll ni = n - x*p;
        if (ni < 0) break;
        ll cnt = 0;
        ll mn = 0;
        for (int i = 0; i < 40; i++) {
            if (ni & (1LL<<i)) {
                cnt += (1LL<<i);
                mn++;
            }
        }
        if (x >= mn && cnt >= x) {
            //x is possible
            cout << x << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
}

