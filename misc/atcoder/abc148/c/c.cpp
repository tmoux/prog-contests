#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int a, b; cin >> a >> b;
    ll ans = (1LL*a*b)/__gcd(a,b);
    cout << ans << endl;
}
