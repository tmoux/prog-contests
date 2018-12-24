#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int N, K, X, a[maxn];
ll dp[2][maxn];

void dnc(int l, int r, int optl, int optr) {
    if (l > r) return;
    int m = (l+r)>>1;
    pair<ll,int> best = {-1,-1};
    for (int k = max(optl,m-K); k <= min(optr,m-1); k++) {
        best = max(best, {dp[0][k],k});
    }
    int opt = best.second;
    if (best.first > 0) dp[1][m] = best.first + a[m];
    dnc(l,m-1,optl,opt);
    dnc(m+1,r,opt,optr);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K >> X;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= K; i++) dp[0][i] = a[i];
    for (int j = 2; j <= X; j++) {
        dnc(1,N,1,N);
        copy(begin(dp[1]),end(dp[1]),begin(dp[0]));
    }
    ll ans = 0;
    for (int i = N-K+1; i <= N; i++) ans = max(ans,dp[0][i]);
    cout << (ans==0?-1:ans) << '\n';

    return 0;
}

