#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, k;
int a[maxn];

int dp[maxn][2];
int f(int i, int j, int x) { //require when j = 0 to be <= x
    int& res = dp[i][j];
    if (res != -1) return res;
    if (i == n) return res = 0;
    res = f(i+1,j,x);
    if (j == 0 && a[i] <= x) {
        res = max(res,1+f(i+1,1,x));
    }
    else if (j == 1) {
        res = max(res,1+f(i+1,0,x));
    }
    return res;
}

bool check(int x) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            dp[i][j] = -1;
        }
    }
    int ans = f(0,0,x);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            dp[i][j] = -1;
        }
    }
    ans = max(ans,f(0,1,x));
    return ans >= k;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int lo = 0, hi = 1e9+1;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        if (check(mid)) {
            hi = mid;
        }
        else lo = mid;
    }
    cout << hi << '\n';
}
