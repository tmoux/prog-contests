#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55;
int n;
char grid[maxn][maxn];

bool valid(int i, int j) {
    return 1 <= i && i <= n && 1 <= j && j <= n;
}

bool canfill(int i, int j) {
    if (!valid(i,j) || grid[i][j] == '#') return false;
    if (!valid(i-1,j) || grid[i-1][j] == '#') return false;
    if (!valid(i+1,j) || grid[i+1][j] == '#') return false;
    if (!valid(i,j-1) || grid[i][j-1] == '#') return false;
    if (!valid(i,j+1) || grid[i][j+1] == '#') return false;
    grid[i][j] = grid[i-1][j] = grid[i+1][j] = grid[i][j-1] = grid[i][j+1] = '#';
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i][j] == '.') {
                if (!canfill(i+1,j)) {
                    cout << "NO\n";
                    return 0;
                }
            }
        }
    }
    cout << "YES" << '\n';

    return 0;
}

