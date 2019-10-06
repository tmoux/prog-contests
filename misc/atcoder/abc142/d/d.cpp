#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int cnt = 0;

void factor(ll x) {
    for (ll i = 2; i*i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                x /= i;
            }
            cnt++;
            factor(x);
            return;
        }
    }
    if (x > 1) cnt++;
}

int main() {
    ll A, B; cin >> A >> B;
    ll gc = __gcd(A,B);
    factor(gc);
    cout << cnt+1 << '\n';
}

