#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
int n, m;
char grid[maxn][maxn];

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
char c;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    set<char> s;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == c) {
                for (int k = 0; k < 4; k++) {
                    int ni = i+dx[k];
                    int nj = j+dy[k];
                    if (0 <= ni && ni < n && 0 <= nj && nj < m && grid[ni][nj] != '.' && grid[ni][nj] != c) {
                        s.insert(grid[ni][nj]);
                    }
                }
            }
        }
    }
    cout << s.size() << endl;
}

