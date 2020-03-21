#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<ll> a(n);
        map<ll,int> mp;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            ll mult = 1;
            while (a[i] > 0) {
                mp[mult] += a[i] % k;
                a[i] /= k;
                mult *= k;
            }
        }
        bool flag = true;
        for (auto p: mp) {
            if (p.second > 1) {
                flag = false;
                break;
            }
        }
        cout << (flag ? "YES" : "NO") << endl;
    }
}

