#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int m; cin >> m;
    ll n = 0, s = 0;
    while (m--) {
        ll d, c; cin >> d >> c;
        n += c;
        s += d*c;
    }
    cout << (n-1+(s-1)/9) << endl;
}

