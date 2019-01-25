#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1100, maxw = 1e4+500;
int N;

struct Block
{
    int val, weight, solid;
} b[maxn];

ll dp[maxn][maxw];

ll f(int i, int ms) {
    if (i == N) return 0LL;
    assert(ms >= 0);
    if (dp[i][ms] >= 0) return dp[i][ms];
    if (b[i].weight > ms) return dp[i][ms] = f(i+1,ms);
    return dp[i][ms] = max(f(i+1,ms),b[i].val+f(i+1,min(ms-b[i].weight,b[i].solid)));    
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) { cin >> b[i].weight >> b[i].solid >> b[i].val; }
    sort(b,b+N,[](auto aa, auto bb) { return aa.weight + aa.solid > bb.weight + bb.solid; });
    memset(dp,-1,sizeof dp);
    ll ans = 0;
    for (int t = 0; t < N; t++) {
        ans = max(ans,b[t].val + f(t+1,b[t].solid));
    }
    cout << ans << '\n';
    return 0;
}
