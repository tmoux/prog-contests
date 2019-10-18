#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 110;
char grid[3][maxn];
bool seen[3][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        memset(seen,0,sizeof seen);
        pair<int,int> start;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == 's') {
                    start = {i,j};
                }
            }
            grid[i][n] = '.';
            grid[i][n+1] = '.';
            grid[i][n+2] = '.';
        }
        queue<pair<int,int>> q;
        q.push(start);
        bool poss = false;
        while (!q.empty()) {
            auto f = q.front(); q.pop();
            //cout << f.first << ' ' << f.second << '\n';
            if (f.second >= n-1) {
                poss = true;
                break;
            }
            //add transitions if possible
            if (grid[f.first][f.second+1] == '.') {
                vector<int> rows;
                for (int d = -1; d <= 1; d++) {
                    //cout << f.first+d << '\n';
                    if (0 <= f.first+d && f.first+d < 3 && grid[f.first+d][f.second+1] == '.') {
                        rows.push_back(f.first+d);
                    }
                }
                for (int r: rows) {
                    if (grid[r][f.second+2] == '.' && grid[r][f.second+3] && !seen[r][f.second+3]) {
                        seen[r][f.second+3] = true;
                        q.push(make_pair(r,f.second+3));
                        //cout << "adding " << r << ' ' << f.second+3 << '\n';
                    }
                }
            }
        }
        cout << (poss ? "YES" : "NO") << '\n';
    }
}

