#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3005;
int n, t;
pair<int,int> a[maxn];
int dp[maxn][maxn];

int f(int i, int j) {
    if (j >= t) return 0;
    if (i >= n) return 0;
    if (dp[i][j] >= 0) return dp[i][j];
    dp[i][j] = f(i+1,j);
    dp[i][j] = max(dp[i][j],a[i].second+f(i+1,j+a[i].first));
    //printf("[%d][%d]: %d\n",i,j,dp[i][j]);
    return dp[i][j];
}

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,-1,sizeof dp);
    cin >> n >> t;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a,a+n,[](auto a, auto b) {
            return a.first < b.first;
            });
    int ans = f(0,0);    
    cout << ans << '\n';
}

