#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 30;
int R, C;
char grid[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cin >> R >> C;
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                cin >> grid[i][j];
            }
        }
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                if (grid[i][j] != '?') {
                    for (int k = j - 1; k >= 1; k--) {
                        if (grid[i][k] != '?') break;
                        grid[i][k] = grid[i][j];
                    }
                    for (int k = j + 1; k <= C; k++) {
                        if (grid[i][k] != '?') break;
                        grid[i][k] = grid[i][j];
                    }
                }
            }
        }
        for (int k = 0; k < 30; k++) {
            for (int i = 1; i <= R; i++) {
                for (int j = 1; j <= C; j++) {
                    if (grid[i][j] == '?') {
                        if (i < R && grid[i+1][j] != '?') grid[i][j] = grid[i+1][j];
                        else if (i > 1 && grid[i-1][j] != '?') grid[i][j] = grid[i-1][j];
                    }
                }
            }
        }
        cout << "Case #" << qq << ":\n";
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                cout << grid[i][j];    
            }
            cout << '\n';
        }
    }

}

