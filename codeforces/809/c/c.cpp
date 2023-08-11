#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int grid[105][105];
int mex(int x, int y) {
    set<int> s;
    for (int j = 0; j < y; j++) {
        s.insert(grid[x][j]);
    }
    for (int i = 0; i < x; i++) {
        s.insert(grid[i][y]);
    }
    for (int i = 1; ; i++) {
        if (!s.count(i)) return i;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            grid[i][j] = mex(i,j);
            cout << grid[i][j] << ' ';
            if (grid[i][j] < 10) cout << ' ';
            if (j % 8 == 7) cout << ' ';
        }
        cout << '\n';
        if (i % 8 == 7) cout << '\n';
    }
}

