#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int N, a[maxn], b[maxn];
int dp[maxn][maxn];

int f(int i, int j) {
    if (i == N || j == N) return 0;
    if (dp[i][j] >= 0) return dp[i][j];
    dp[i][j] = max(f(i+1,j),f(i,j+1));
    if (abs(a[i]-b[j]) <= 4) {
        dp[i][j] = max(dp[i][j],1+f(i+1,j+1));
    }
    return dp[i][j];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //freopen("nocross.in","r",stdin); freopen("nocross.out","w",stdout);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < N; i++) cin >> b[i];
    memset(dp,-1,sizeof dp);
    int ans = f(0,0);
    cout << ans << '\n';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << f(i,j) << ' ';
        }
        cout << '\n';
    }

    return 0;
}

