#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> dp(n+1);
    int ans = 0;
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        if (dp[a[i]-1]) {
            dp[a[i]] = 1;
            ans = max(ans,a[i]);
        }
    }
    if (ans == 0) {
        cout << -1 << '\n';
    }
    else {
        cout << n-ans << endl;
    }
}
