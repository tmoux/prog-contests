#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//what's longest consec. decreasing sequence 
//starting at given point
const int maxn = 1e5+5;
int n, m, a[maxn];
int b[maxn];

int start[maxn];

int dp[maxn];
ll solve() {
    memset(start,0,sizeof start);
    for (int i = 1; i <= m; i++) {
        b[i] = a[i] - i;
        if (b[i] >= 1 && start[b[i]] == 0) {
            start[b[i]] = i;
        }
    }
    map<int,int> mp;
    memset(dp,0,sizeof dp);
    for (int i = m; i >= 1; i--) {
        if (mp.count(b[i]-1)) {
            dp[i] = dp[mp[b[i]-1]] + 1;
        }
        else dp[i] = 1;
        mp[b[i]] = i;
        //printf("%d: b[%d] = %d, dp[%d] = %d, start[%d] = %d\n",i,i,b[i],i,dp[i],i,start[i]);
        //cout << i << ": " << dp[i] << '\n';
        //cout << i << " start: " << start[i] << '\n';
    }
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        int total = m+1;
        if (start[i] != 0) {
            total -= dp[start[i]];
        }
        total = min(total,n-i);
        //cout << i << ": " << total << '\n';
        res += total;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    ll ans = n;
    ans += solve();
    for (int i = 1; i <= m; i++) {
        a[i] = n-a[i]+1;
    }
    ans += solve();
    cout << ans << '\n';
}

