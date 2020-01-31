#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 22;
int h, w;
char grid[maxn][maxn];

int dist[maxn][maxn];

int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};

bool valid(int r, int c) {
    return 0 <= r && r < h && 0 <= c && c < w;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> grid[i][j];
        }
    }
    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == '#') continue;
            queue<pair<int,int>> q;
            memset(dist,-1,sizeof dist);
            q.push({i,j});
            dist[i][j] = 0;
            while (!q.empty()) {
                auto p = q.front(); q.pop();
                ans = max(ans,dist[p.first][p.second]);
                for (int k = 0; k < 4; k++) {
                    int ni = p.first+dx[k];
                    int nj = p.second+dy[k];
                    if (!valid(ni,nj) || grid[ni][nj] == '#') continue;
                    if (dist[ni][nj] == -1 || dist[ni][nj] > dist[p.first][p.second] + 1) {
                        dist[ni][nj] = dist[p.first][p.second] + 1;
                        q.push({ni,nj});
                    }
                }
            }
        }
    }
    cout << ans << '\n';
}

