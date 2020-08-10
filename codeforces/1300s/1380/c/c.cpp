#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; 
        ll x;
        cin >> n >> x;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(),a.end(),greater<ll>());
        int ans = 0;
        int cur = 0;
        for (int i = 0; i < n; i++) {
            if (a[i]*(cur+1) >= x) {
                ans++;
                cur = 0;
            }
            else {
                cur++;
            }
        }
        cout << ans << '\n';
    }
}
