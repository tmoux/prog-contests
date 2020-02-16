#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    int tt; cin >> tt;
    while (tt--) {
        int n, k; cin >> n >> k;
        vector<int> a(n);
        vector<int> b(n,0), c(n,0);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] % k != 0) {
                b[i] = a[i] % k;
                c[i] = k - b[i];
            }
        }
        ll take = 0, give = 0;
        for (int i = 0; i < n; i++) {
            give += c[i];
        }
        ll r = give == 0 ? 0 : 1e18;
        for (int i = 0; i < n; i++) {
            take += b[i];
            give -= c[i];
            if (take >= give) {
                r = min(r,(take-give)%k);
            }
        }
        cout << r << '\n';
    }
}
