#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int grid[maxn][maxn];

int cnt(int x, int y) {
    int res = 0;
    for (int i = x-1; i <= x+1; i++) {
        for (int j = y-1; j <= y+1; j++) {
            res += grid[i][j];
        }
    }
    return res;
}

int main()
{
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        memset(grid,0,sizeof grid);
        int A; cin >> A;
        for (int i = 2; i <= 68; i += 3) {
            bool done = false;
            while (cnt(i,2) < 9) {
                cout << i << ' ' << 2 << endl;
                int x, y; cin >> x >> y;
                if (x == 0 && y == 0) {
                    done = true;
                    break;
                }
                grid[x][y] = 1;
            }
            if (done) break;
        }
    }

}

