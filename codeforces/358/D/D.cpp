#include <bits/stdc++.h>
using namespace std;

const int maxn = 3005;
int b[maxn][3], dp[maxn][2], n;

int f(int i, bool j) {
    if (dp[i][j] >= 0) return dp[i][j];    
    if (i == n-1) {
        if (!j) return dp[i][j] = b[i][0];
        else return dp[i][j] = b[i][1];
    }
    if (!j) {
        return dp[i][j] = max(f(i+1,1)+b[i][0],f(i+1,0)+b[i][1]);
    }
    else {
        return dp[i][j] = max(f(i+1,1)+b[i][1],f(i+1,0)+b[i][2]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //input
    cin >> n;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[j][i];
        }
    }
    //get answer
    memset(dp,-1,sizeof(dp));
    int ans = f(0,0);
    cout << ans << '\n';

    return 0;
}
	

