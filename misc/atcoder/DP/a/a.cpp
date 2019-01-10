#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int N, a[maxn];
int dp[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = N - 1; i >= 1; i--) {
        if (i == N - 1) dp[i] = abs(a[i] - a[i+1]);
        else {
            dp[i] = min(abs(a[i]-a[i+1]) + dp[i+1],
                        abs(a[i]-a[i+2]) + dp[i+2]);
        }
    }
    cout << dp[1] << '\n';


    return 0;
}

