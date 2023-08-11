#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int k, n;
const int maxn = 2e3+5;
char grid[maxn][maxn];
int pre[maxn][maxn];

int sum(int x1, int y1, int x2, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    return pre[x2][y2] - pre[x1-1][y2] - pre[x2][y1-1] + pre[x1-1][y1-1];
}

int cols[maxn][maxn];
int rows[maxn][maxn];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            grid[i][j] = c;
            pre[i][j] = c == 'B' ? 1 : 0;
            //pre[i][j] += pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
        }
    }
    for (int i = 1; i <= n+5; i++) {
        for (int j = 1; j <= n+5; j++) {
            pre[i][j] += pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
        }
    }
    int currCols = 0;
    for (int i = 1; i <= n; i++) {
        if (sum(1,i,n,i) == 0) currCols++;
    }
    int currRows = 0;
    for (int i = 1; i <= n; i++) {
        if (sum(i,1,i,n) == 0) currRows++;
    }
    for (int i = 1; i+k-1 <= n; i++) {
        int curr = currCols;
        for (int j = 1; j <= k; j++) {
            if (sum(1,j,i-1,j) + sum(i+k,j,n,j) == 0 &&
                sum(1,j,n,j) > 0) {
                curr++;
            }
        }
        for (int j = 1; j + k - 1 <= n; j++) {
            cols[i][j] = curr;
            //printf("[%d][%d]: %d\n",i,j,curr);
            if (sum(1,j,i-1,j) + sum(i+k,j,n,j) == 0 &&
                sum(1,j,n,j) > 0) curr--;
            if (sum(1,j+k,i-1,j+k) + sum(i+k,j+k,n,j+k) == 0 &&
                sum(1,j+k,n,j+k) > 0) curr++;
        }
    }
    for (int j = 1; j+k-1 <= n; j++) {
        int curr = currRows;
        for (int i = 1; i <= k; i++) {
            if (sum(i,1,i,j-1) + sum(i,j+k,i,n) == 0 &&
                sum(i,1,i,n) > 0) {
                curr++;
            }
        }
        for (int i = 1; i + k - 1 <= n; i++) {
            //cout << (sum(i,0,i,j-1) + sum(i,j+k,i,n+1)) << '\n';
            rows[i][j] = curr;
            //printf("[%d][%d]: %d\n",i,j,curr);
            if (sum(i,1,i,j-1) + sum(i,j+k,i,n) == 0 &&
                sum(i,1,i,n) > 0) curr--;
            if (sum(i+k,1,i+k,j-1) + sum(i+k,j+k,i+k,n) == 0 &&
                sum(i+k,1,i+k,n) > 0) curr++;
        }
    }   
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mx = max(mx,cols[i][j] + rows[i][j]);            
        }
    }
    cout << mx << '\n';
}

