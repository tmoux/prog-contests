#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e3+5;
const ll inf = 1LL<<60;
int N;
ll A[maxn], pre[maxn];
ll dp[maxn][maxn];
int a, b;

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    cin >> a >> b;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        pre[i] = pre[i-1] + A[i];
    }
    for (int i = 0; i <= N; i++) {
        for (int k = 0; k <= N; k++) {
            dp[i][k] = inf;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= N; i++) {
        for (int k = 1; k <= N; k++) {
            dp[i][k] = inf;
            for (int j = 0; j < i; j++) {
                //cout << j << ' ' << (dp[j][k-1]|(pre[i]-pre[j])) << '\n';
                dp[i][k] = min(dp[i][k],
                               dp[j][k-1]|(pre[i]-pre[j]));
                //cout << dp[i][k] << '\n';
            }
            //printf("[%d][%d]: %lld\n",i,k,dp[i][k]);
        }
    }
    ll ans = inf;
    for (int i = a; i <= b; i++) {
        ans = min(ans,dp[N][i]);
    }
    cout << ans << '\n';
}

