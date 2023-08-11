#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            char c; cin >> c;
            a[i] = c-'0';
            --a[i];
        }
        map<int,int> mp;
        mp[0] = 1;
        int sum = 0;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i];
            if (mp.count(sum)) ans += mp[sum];
            mp[sum]++;
        }
        cout << ans << '\n';
    }
}

