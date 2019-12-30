#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];

int dp[maxn];
int cnt[maxn];

bool use[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    for (int i = n; i >= 1; i--) {
        if (cnt[i] == 0) dp[i] = dp[i+1];
        else {
            dp[i] = min(1+dp[i+2],1+dp[i+3]);
        }
    }
    int mn = dp[1];
    int mx = 0;
    sort(a,a+n);
    for (int i = 0; i < n; i++) {
        if (!use[a[i]-1]) {
            use[a[i]-1] = true;
            mx++;
        }
        else if (!use[a[i]]) {
            use[a[i]] = true;
            mx++;
        }
        else if (!use[a[i]+1]) {
            use[a[i]+1] = true;
            mx++;
        }
    }
    cout << mn << ' ' << mx << endl;
}

