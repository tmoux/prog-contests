#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105, maxk = 1e5+5;
int N, K, a[maxn];
int dp[2][maxk];

int f(bool i, int k) {
    if (dp[i][k] != -1) return dp[i][k];
    if (k == 0) return dp[i][k] = !i;
    bool poss = false;
    for (int j = 1; j <= N; j++) {
        if (k-a[j] >= 0) {
            if (f(!i,k-a[j]) == i) {
                poss = true;
                dp[i][k] = i;
                break;
            }
        }
    }
    if (poss) return dp[i][k];
    else return dp[i][k] = !i;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> a[i];
    memset(dp,-1,sizeof dp);
    int ans = f(0,K);
    cout << (ans == 0 ? "First" : "Second") << '\n';

    return 0;
}

