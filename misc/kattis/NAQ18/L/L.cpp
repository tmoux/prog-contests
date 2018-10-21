#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, k;
int grid[maxn][maxn];
set<int> rows[maxn], cols[maxn];

bool dfs(int r, int c) {
    //cout << r << ' ' << c << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //cout << grid[i][j] << ' ';
        }
        //cout << '\n';
    }
    if (r == n) return true;
    int nr = c == n - 1 ? r+1 : r;
    int nc = c == n - 1 ? 0 : c+1;
    for (int i = 1; i <= n; i++) {
        if (!rows[r].count(i) && !cols[c].count(i)) {
            //try placing it
            rows[r].insert(i);
            cols[c].insert(i);
            grid[r][c] = i;
            //cout << r << ' ' << c << ": " << i << '\n';
            //cout << cols[1].count(1) << '\n';
            if (dfs(nr,nc)) return true;
            grid[r][c] = 0;
            rows[r].erase(i);
            cols[c].erase(i);
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (rows[i].count(grid[i][j]) || cols[j].count(grid[i][j])) {
                cout << "no\n";
                return 0;
            }
            rows[i].insert(grid[i][j]);
            cols[j].insert(grid[i][j]);
        }
    }
    if (dfs(k,0)) {
        cout << "yes" << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << grid[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    else cout << "no\n";

    return 0;
}

