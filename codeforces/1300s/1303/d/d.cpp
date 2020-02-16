#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int lg(int x) {
    int r = 0;
    while (x/2 > 0) {
        r++;
        x /= 2;
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll n; int m;
        cin >> n >> m;
        vector<int> a(m);
        vector<int> d(65,0);
        ll sum = 0;
        for (int i = 0; i < m; i++) {
            cin >> a[i];
            sum += a[i];
            d[lg(a[i])]++;
        }
        if (sum < n) {
            cout << -1 << '\n';
            continue;
        }
        ll cur = 0;
        ll ans = 0;
        for (int i = 0; i <= 60; i++) {
            cur += d[i];
            if (n & (1LL<<i)) {
                if (cur > 0) {
                    cur--;
                }
                else {
                    for (int j = i+1; j <= 60; j++) {
                        if (d[j] > 0) {
                            d[j]--;
                            cur += 1LL<<(j-i);
                            ans += j-i;
                            break;
                        }
                    }
                    if (cur == 0) {
                        cout << -1 << '\n';
                        goto done;
                    }
                    cur--;
                }
            }
            cur /= 2;
        }
        cout << ans << '\n';
        done:
        int x = 69;
    }
}

