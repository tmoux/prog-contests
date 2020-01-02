#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll x, y; cin >> x >> y;
    int ans = 0;
    while (x <= y) {
        x *= 2;
        ans++;
    }
    cout << ans << '\n';
}

