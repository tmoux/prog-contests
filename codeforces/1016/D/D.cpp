#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, m, row[maxn], col[maxn];
int grid[maxn][maxn];

int currow[maxn], curcol[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    int curr = 0;
    for (int i = 0; i < n; i++) {
        cin >> row[i];
        curr ^= row[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> col[i];
        curr ^= col[i];
    }

    if (curr != 0) {
        cout << "NO" << '\n';
        return 0;
    }
    //possible
    int realcurr = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == n - 1 && j == m - 1) {
                grid[i][j] = col[m-1] ^ realcurr;
            }
            else if (j == m - 1) {
                grid[i][j] = row[i];
                realcurr ^= grid[i][j];
            }
            else if (i == n - 1) {
                grid[i][j] = col[j];
            }
            else {
                grid[i][j] = 0;
            }
        }
    }
    
    cout << "YES" << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    

    return 0;
}
	

