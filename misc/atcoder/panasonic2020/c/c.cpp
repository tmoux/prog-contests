#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll a, b, c; cin >> a >> b >> c;
    ld t = a + b - c + 2*sqrtl(a*b);
    cout << (signbit(t) ? "Yes" : "No") << endl;
}

