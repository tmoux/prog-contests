#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int h, w;
char grid[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> h >> w;
    int cnt = 0;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '*') cnt++;
        }
    }

    for (int i = 2; i < h; i++) {
        for (int j = 2; j < w; j++) {
            if (grid[i][j] != '*') continue;
            int c = 1;
            //cout << i << ' ' << j << ": " << cnt << '\n';
            if (grid[i-1][j] != '*') continue;
            for (int k = i-1; k >= 1; k--) {
                if (grid[k][j] != '*') break;
                c++;
            }

            if (grid[i+1][j] != '*') continue;
            for (int k = i+1; k <= h; k++) {
                if (grid[k][j] != '*') break;
                c++;
            }

            if (grid[i][j-1] != '*') continue;
            for (int k = j-1; k >= 1; k--) {
                if (grid[i][k] != '*') break;
                c++;
            }
            
            if (grid[i][j+1] != '*') continue;
            for (int k = j+1; k <= w; k++) {
                if (grid[i][k] != '*') break;
                c++;
            }

            //cout << i << ' ' << j << ": " << c << ' ' << cnt << '\n';
            if (c == cnt) {
                cout << "YES\n";
                return 0;
            }
        }
    }
    cout << "NO\n";
}

