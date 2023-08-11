#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int root(ll x) {
    int sum = 0;
    while (x) {
        sum += x % 10;
        x /= 10;
    }
    return sum < 10 ? sum : root(sum);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    while (n--) {
        ll k, x; cin >> k >> x;
        if (k == 1) cout << x << '\n';
        else {
            ll ans = (k-1)*9 + x;
            cout << ans << '\n';
        }
    }

    return 0;
}

