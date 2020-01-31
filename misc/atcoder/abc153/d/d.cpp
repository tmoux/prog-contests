#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll H; cin >> H;
    ll cnt = 1;
    ll ans = 0;
    while (H > 0) {
        ans += cnt;
        cnt *= 2;
        H /= 2;
    }
    cout << ans << endl;
}
