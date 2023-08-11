#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;
int x[maxn], a[maxn];
int dp[maxn];
void solve() {
    cin >> n >> k;
    for (int i = 0; i <= n; i++) {
        x[i] = 0;
        a[i] = 0;
        dp[i] = 0;
    }
    map<int,int> mp;
    map<int,int> compress;
    vector<int> xs(n), ys(n);
    for (int i = 0; i < n; i++) {
        cin >> xs[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> ys[i];
    }
    for (int i = 0; i < n; i++) {
        int x = xs[i];
        int y = ys[i];
        ++mp[x];
    }
    int pt = 1;
    for (auto p: mp) {
        a[pt] = p.second;
        a[pt] += a[pt-1];
        x[pt] = p.first;
        pt++;
    }
    int lp = 0;
    int ans = 0;
    for (int i = 1; i < pt; i++) {
        while (x[i]-k > x[lp+1]) {
            lp++;
        }
        dp[i] = a[i]-a[lp];
        //cout << "lp = " << x[lp] << endl;
        //cout << x[i] << ": " << dp[i] << endl;
        ans = max(ans,dp[i]+dp[lp]);
        dp[i] = max(dp[i],dp[i-1]); 
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
