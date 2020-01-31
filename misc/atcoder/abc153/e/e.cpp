#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxh = 10004, maxn = 1005;
int H, N, a[maxn], b[maxn];

int dp[maxh];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> H >> N;
    for (int i = 0; i < N; i++) {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= H; i++) {
        dp[i] = 2e9+9;
        for (int j = 0; j < N; j++) {
            dp[i] = min(dp[i],dp[max(0,i-a[j])]+b[j]);
        }
    }
    cout << dp[H] << endl;
}

