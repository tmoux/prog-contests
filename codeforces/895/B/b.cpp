#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, x, k; cin >> n >> x >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    ll ans = 0;
    for (int i: a) {
        int y = i % x == 0 ? i : (i/x+1)*x;
        ll bound = y + 1LL*(k-1)*x;
        auto it = lower_bound(a.begin(),a.end(),max((ll)i,bound));
        auto it2 = lower_bound(a.begin(),a.end(),max((ll)i,bound+x));
        ans += distance(it,it2);
    }
    cout << ans << '\n';
}

