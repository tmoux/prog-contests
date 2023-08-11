#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 99;
int n, k;
bool grid[4][maxn];
int dp[4][maxn];

int f(int i, int j)
{
    if (dp[i][j] != 0) return dp[i][j];
    if (grid[i][j] || i < 0 || j < 0) return 0;
    if (i == 0 && j == 0) return dp[i][j] = 1;
    return dp[i][j] = f(i-1,j) + f(i,j-1);
}

void flipgrid()
{
    memset(dp,0,sizeof(dp));
    bool tmp[4][maxn];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            tmp[i][j] = grid[3-i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = tmp[i][j];
        }
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            char c; cin >> c;
            grid[i][j] = (c == '#');
        }
    }
    cout << f(3,n-1) << '\n';
    flipgrid();
    cout << f(3,n-1) << '\n';
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
	

