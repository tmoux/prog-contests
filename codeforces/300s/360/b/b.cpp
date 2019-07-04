#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005, INF = 2e9;
int n, k, a[maxn];
int D;

int dp[maxn];
int f() {
    for (int i = 0; i <= n; i++) dp[i] = INF;
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        dp[i] = i;
        for (int j = 0; j < i; j++) {
            if ((abs(a[i]-a[j])+(i-j)-1)/(i-j)<=D) {
                dp[i] = min(dp[i],dp[j]+i-j-1);
            }
        }
    }
    int mn = INF;
    for (int i = 0; i < n; i++) {
        mn = min(mn,dp[i]+n-i-1);
    }
    return mn <= k;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int lo = -1, hi = 2e9+9;
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        D = mid;
        if (f()) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
    cout << hi << '\n';
}

