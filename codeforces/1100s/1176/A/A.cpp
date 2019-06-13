#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        ll n; cin >> n;
        int ans = 0;
        while (n % 2 == 0) {
            n /= 2;
            ans++;
        }
        while (n % 3 == 0) {
            n /= 3;
            ans += 2;
        }
        while (n % 5 == 0) {
            n /= 5;
            ans += 3;
        }
        if (n != 1) {
            cout << -1 << '\n';
        }
        else {
            cout << ans << '\n';
        }
    }
}

