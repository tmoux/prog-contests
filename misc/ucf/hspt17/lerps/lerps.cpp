#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 505;
int dp[maxn][maxn];
int pref[maxn];
int n;

int f(int i, int j) {
    if (dp[i][j] >= 0) return dp[i][j];
    if (i == n) {
        if ((pref[i]-pref[j-1]) % 2 == 0) return dp[i][j] = pref[i]-pref[j-1];
        else return dp[i][j] = 0;
    }
    if ((pref[i]-pref[j-1]) % 2 == 1) {
        return dp[i][j] = max(f(i+1,i+1),f(i+1,j));
    }
    else {
        return dp[i][j] = max(pref[i]-pref[j-1]+f(i+1,i+1),f(i+1,j));
    }
}

void solve(int t) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = -1;
        }
    }
    memset(pref,0,sizeof pref);
    for (int i = 1; i <= n; i++) {
        cin >> pref[i];
        pref[i] += pref[i-1];
    }
    int ans = f(1,1);
    printf("Environment #%d: %d lerps\n",t,ans);
}

int main()
{
    int t; cin >> t;
    for (int i = 1; i <= t; i++) solve(i);

    return 0;
}

