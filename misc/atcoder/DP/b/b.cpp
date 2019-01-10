#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, a[maxn];
int K;
int dp[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = N - 1; i >= 1; i--) {
        dp[i] = 2e9+9;
        for (int j = i + 1; j <= min(N,i+K); j++) {
            dp[i] = min(dp[i],dp[j] + abs(a[i]-a[j]));
        }
    }
    cout << dp[1] << '\n';


    return 0;
}

