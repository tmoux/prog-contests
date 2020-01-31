#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n;
int q;

ll solve(ll n, ll x) {
    //cout << n << ' ' << x << '\n';
    if (x % 2 == 1) {
        return (x+1)/2;
    }
    else {
        ll nn = n/2;
        if (n % 2 == 0) {
            ll nx = x/2;
            return (n-n/2) + solve(nn,nx);
        }
        else {
            ll nx = (x)/2-1;
            if (nx == 0) nx = nn;
            return (n-n/2) + solve(nn,nx);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    while (q--) {
        ll xi; cin >> xi;
        cout << solve(n,xi) << '\n';
    }
}

