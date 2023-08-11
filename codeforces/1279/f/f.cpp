#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, k, l;
int a[maxn];
int pre[maxn];
pair<ll,int> dp[maxn];

ll solve() {
    ll lo = 0, hi = l+5;
    ll ans = 0;
    while (lo <= hi) {
        ll lambda = (lo+hi)/2;
        for (int i = 1; i <= l; i++) {
            dp[i] = max(dp[i-1],{pre[i]-lambda,-1});
        }
        for (int i = l+1; i <= n; i++) {
            dp[i] = max(dp[i-1],{dp[i-l].first+pre[i]-pre[i-l]-lambda,dp[i-l].second-1});
        }
        if (-dp[n].second <= k) {
            hi = lambda-1;
            /*
            ans = pre[n]-(dp[n].first-lambda*dp[n].second);
            cout << lambda << ": " << ans << endl;
            cout << dp[n].second << endl;
            */
            ans = dp[n].first;
        }
        else lo = lambda+1;
    }
    return pre[n]-k*lo-ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k >> l;
    string s; cin >> s;
    if (1LL*k*l >= n) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 0; i < n; i++) {
        a[i+1] = ('A' <= s[i] && s[i] <= 'Z');
    }
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i-1] + a[i];
    }
    ll ans = solve(); 

    for (int i = 1; i <= n; i++) {
        a[i] = 1-a[i];
        pre[i] = pre[i-1] + a[i];
    }
    ans = min(ans,solve());
    cout << ans << endl;
}

