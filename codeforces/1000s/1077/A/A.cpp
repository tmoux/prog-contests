#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b, k; cin >> a >> b >> k;
        ll ans = 1LL*(a-b) * (k/2);
        if (k%2) ans += a;
        cout << ans << '\n';
    }

    return 0;
}

