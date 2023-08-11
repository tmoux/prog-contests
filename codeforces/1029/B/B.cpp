#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2e5+5;
int n, A[maxn], dp[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> A[i];
    dp[n-1] = 1;
    int ans = 1;
    for (int i = n - 2; i >= 0; i--) {
        if (A[i] * 2 >= A[i+1]) dp[i] = dp[i+1] + 1;
        else dp[i] = 1;
        ans = max(ans,dp[i]);
    }
    cout << ans << '\n';

    return 0;
}
	

