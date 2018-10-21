#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 120;
int n, m;
bool grid[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            grid[i][j] = s[j] == 'B';
        }
    }
    int x = -1;
    int s = -1, e = -1;
    for (int i = 0; i < n; i++) {
        if (x != -1) break;
        for (int j = 0; j < m; j++) {
            if (grid[i][j]) {
                if (j == 0 || !grid[i][j-1]) {
                    s = j;
                }
                if (j == m - 1 || !grid[i][j+1]) {
                    e = j;
                }
            }
        }
        if (s != -1) x = (s+e)/2;
    }

    int y = -1;
    s = -1, e = -1;
    for (int j = 0; j < m; j++) {
        if (y != -1) break;
        for (int i = 0; i < n; i++) {
            if (grid[i][j]) {
                if (i == 0 || !grid[i-1][j]) {
                    s = i;
                }
                if (i == n - 1 || !grid[i+1][j]) {
                    e = i;
                }
            }
        }
        if (s != -1) y = (s+e)/2;
    }

    cout << (y+1) << ' ' << (x+1) << '\n';

    return 0;
}
	

