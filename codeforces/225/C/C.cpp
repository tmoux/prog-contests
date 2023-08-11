#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 1005;
const int INF = 2000000007;
int n, m, x, y;
bool grid[maxn][maxn];
int cost[maxn][2];

int dp[maxn][maxn][2]; //0 is black, 1 is white
//dp[i][j][k] is min cost for col i with j rows of color k before it

int f(int i, int j, bool k) {
    if (dp[i][j][k] >= 0) return dp[i][j][k];
    if (i == m) {
        if (x <= j && j <= y) {
            //valid
            return dp[i][j][k] = 0;
        }
        else return dp[i][j][k] = INF;
    }
    
    if (j == y) {
        return dp[i][j][k] = cost[i][!k] + f(i+1,1,!k);
    }
    if (j < x) {
        return dp[i][j][k] = cost[i][k] + f(i+1,j+1,k);
    }
   
    return dp[i][j][k] = min(cost[i][k] + f(i+1,j+1,k),
                             cost[i][!k] + f(i+1,1,!k));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    //setup and input
    memset(dp,-1,sizeof(dp));
    cin >> n >> m >> x >> y;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            grid[i][j] = s[j] == '.';
        }
    }

    for (int j = 0; j < m; j++) {
        int c = 0;
        for (int i = 0; i < n; i++) {
            if (!grid[i][j]) c++;
        }
        cost[j][1] = c;
    }
    for (int j = 0; j < m; j++) {
        cost[j][0] = n - cost[j][1];
    }
    //calculate dp
    int ans = min(f(0,0,0),f(0,0,1));
    cout << ans << '\n';


    return 0;
}
	

