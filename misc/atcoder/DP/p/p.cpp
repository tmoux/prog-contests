#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, M = 1e9+7;
int N;
vector<int> adj[maxn];

ll dp[2][maxn]; //0 = white, 1 = black
//dp[0] means parent is white

int sum(int a, int b) {
    return (a+b) % M;
}

ll f(int t, int i, int p) {
    if (dp[t][i] != -1) return dp[t][i];
    dp[t][i] = 1;
    for (int j: adj[i]) {
        if (j == p) continue;
        if (t == 0) {
            dp[t][i] = (1LL*dp[t][i]*sum(f(0,j,i),f(1,j,i))) % M;
        }
        else {
            dp[t][i] = (1LL*dp[t][i]*f(0,j,i)) % M;
        }
    }
    return dp[t][i];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    memset(dp,-1,sizeof dp);
    ll ans = (f(0,1,1) + f(1,1,1)) % M;
    cout << ans << '\n';

    return 0;
}

