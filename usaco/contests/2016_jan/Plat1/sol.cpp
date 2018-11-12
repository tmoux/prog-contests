#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 205;
int n, m;
bool grid[maxn][maxn];
int dp[maxn][maxn][maxn]; //max cols can be built so far
int pfx[maxn][maxn];

bool isClear(int i, int j, int c) {
    return pfx[j][c] - pfx[i-1][c] == 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("fortmoo.in","r",stdin); freopen("fortmoo.out","w",stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c; cin >> c;
            grid[i][j] = c == '.';
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pfx[i][j] += pfx[i-1][j] + !grid[i][j];    
        }
    }
    int maxarea = 0;
    for (int col = 1; col <= m; col++) {
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                if (isClear(i,j,col)) {
                    int r = (j-i+1)*(dp[i][j][col-1]+1);
                    maxarea = max(maxarea,r);
                }
                if (dp[i][j][col-1] == 0) {
                    dp[i][j][col] = isClear(i,j,col);    
                }
                else if (grid[i][col] && grid[j][col]) {
                    dp[i][j][col] = dp[i][j][col-1] + 1;        
                }
            }
        }
    }
    cout << maxarea << '\n';

    /*
    for (int col = m; col >= 1; col--) {
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                cout << dp[i][j][col] << ' ';
            }
            cout << '\n';
        }
    }
    */
    

    return 0;
}

