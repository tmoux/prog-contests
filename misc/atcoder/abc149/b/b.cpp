#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll a, b, k; cin >> a >> b >> k;
    ll mn = min(a,k);
    a -= mn;
    k -= mn;
    b -= min(b,k);
    cout << a << ' ' << b << '\n';
}

