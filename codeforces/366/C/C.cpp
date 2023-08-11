#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 105;
const int maxv = 40000;
const int midv = 20000;
int n, k;
int value[maxn], cal[maxn], volume[maxn];
int dp[maxn][maxv];

int f(int i, int b) {
    if (i == 0 && b == midv) return dp[i][b];
    if (dp[i][b] != 0) return dp[i][b];
    if (i == 0) return -1;
    int m1 = f(i-1,b-volume[i]);
    int m2 = f(i-1,b);
    if (m1 != -1 && m2 != -1) return dp[i][b] = max(m1+value[i],m2);
    if (m1 != -1 && m2 == -1) return dp[i][b] = m1+value[i];
    if (m1 == -1 && m2 != -1) return dp[i][b] = m2;
    return dp[i][b] = -1;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,0,sizeof(dp));
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> cal[i];
        volume[i] = value[i] - k*cal[i];
    }
    dp[0][midv] = 0;
    int ans = f(n,midv);    
    cout << (ans ? ans : -1) << '\n';

    return 0;
}
	

