#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    const ll INF = 1e18;
    auto solve = [&n](vector<ll>& a, ll x) {
        vector<ll> b(n);
        ll y = 1;
        ll ret = 0;
        for (int i = 0; i < n; i++) {
            b[i] = y;
            if (y > INF/x) {
                return INF;
            }
            ll ny = y*x;
            y = ny;
            ret += abs(a[i]-b[i]);
            if (ret < 0) return INF;
        }
        return ret;
    };
    sort(a.begin(),a.end());
    if (a.size() >= 70) {
        cout << solve(a,1) << '\n';
    }
    else {
        ll ans = INF;
        for (int i = 1; i <= 100000; i++) {
            ans = min(ans,solve(a,i));
        }
        cout << ans << '\n';
    }
}
