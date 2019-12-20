#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, a[maxn];
int dp[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        dp[a[i]] = dp[a[i]-1] + 1;
        ans = max(ans,dp[a[i]]);
    }
    cout << n-ans << '\n';
}
