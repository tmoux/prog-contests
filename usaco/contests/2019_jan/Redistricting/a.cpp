#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int N, K;
char a[maxn];
int pre[maxn];
int dp[maxn];

int main()
{
    //freopen("redistricting.in","r",stdin); freopen("redistricting.out","w",stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        pre[i] = a[i] == 'G' ? 1 : -1;
        pre[i] += pre[i-1];
    }
    for (int i = 1; i <= N; i++) {
        dp[i] = maxn;
        for (int j = max(i-K,0); j < i; j++) {
            int d = (pre[i] - pre[j] >= 0 ? 1 : 0);
            dp[i] = min(dp[i],dp[j] + d); 
        }
    }
    cout << dp[N] << '\n';

    return 0;
}

