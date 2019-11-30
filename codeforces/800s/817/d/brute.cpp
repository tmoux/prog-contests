#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int mn = a[i];
        int mx = a[i];
        for (int j = i; j < n; j++) {
            mn = min(mn,a[j]);
            mx = max(mx,a[j]);
            ans += mx-mn;
        }
    }
    cout << ans << '\n';
}

