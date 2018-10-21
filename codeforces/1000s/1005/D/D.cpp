#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 200005;
int n, A[maxn];
int dp[maxn][3];

int f(int i, int res) {
    if (dp[i][res] >= 0) return dp[i][res];
    if (i == n) return dp[i][res] = res == 0 ? 1 : 0;
    res = (res + A[i]) % 3;
    if (res == 0) return dp[i][res] = 1 + f(i+1,res);
    else {
        return dp[i][res] = max(f(i+1,res), f(i+1,0));
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    n = s.size();
    for (int i = 0; i < n; i++) {
        A[i] = s[i] - '0';
    }
    memset(dp,-1,sizeof(dp));
    int ans = f(0,0);
    cout << ans << '\n';

    return 0;
}
	

