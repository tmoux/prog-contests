#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll x; cin >> x;
        ll n = 1;
        int ans = 0;
        while (n*(n+1)/2 <= x) {
            ans++;
            x -= n*(n+1)/2;
            n = n*2+1;
        }
        cout << ans << '\n';
    }
}
