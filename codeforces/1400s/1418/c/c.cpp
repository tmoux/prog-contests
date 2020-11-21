#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int INF = 1e9;
const int maxn = 2e5+5;

int n;
int a[maxn];
int dp[maxn][2];

int f(int i, int j) {
    if (i == -1) {
        return j==0?INF:0;
    }
    int& res = dp[i][j];
    if (res != -1) return res;
    res = f(i-1,j^1) + ((j==0)&&a[i]);
    if (i-2 >= -1) {
        res = min(res,
            f(i-2,j^1) + ((j==0)&&a[i]) + ((j==0)&&a[i-1]));
    }
    return res;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            dp[i][j] = -1;
        }
    }
    int ans = min(f(n-1,0),f(n-1,1));
    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cout << i << ' ' << j << ": " << f(i,j) << '\n';
        }
    }
    */
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
