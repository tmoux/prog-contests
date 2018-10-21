#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isPrime(ll x) {
    if (x == 1) return true;
    for (ll i = 2; i*i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

void solve() {
    ll a, b; cin >> a >> b;
    cout << (isPrime(a+b) && (a-b == 1) ? "YES" : "NO") << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t; while (t--) solve();
    return 0;
}

