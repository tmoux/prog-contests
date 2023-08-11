#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int S(ll x) {
    int r = 0;
    while (x) {
        r += x % 10;
        x /= 10;
    }
    return r;
}

ll make0(ll n, int i) {
    ll r = 1;
    for (int j = 0; j < i; j++) r *= 10;
    ll add = r-(n%r);
    return n+add;
}

void solve() {
    ll n;
    int s;
    cin >> n >> s;
    for (int i = 0; i <= 20; i++) {
        if (S(n+i) <= s) {
            cout << i << '\n';
            return;
        }
    }
    for (int i = 1; i <= 18; i++) {
        ll nn = make0(n,i);
        //cout << i << ": " << nn << endl;
        ll cnt = nn-n;
        if (S(nn) <= s) {
            cout << cnt << '\n';
            return;
        }
    }
    assert(false);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
