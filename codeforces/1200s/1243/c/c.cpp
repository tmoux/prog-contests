#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n; cin >> n;
    ll gc = 0;
    for (ll i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            gc = __gcd(gc,i);
            gc = __gcd(gc,n/i);
        }
    }
    if (gc == 0) {
        cout << n << '\n';
    }
    else {
        cout << gc << '\n';
    }
}

