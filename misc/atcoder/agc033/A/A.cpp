#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int H, W;
const int maxn = 1005;
char grid[maxn][maxn];
int dist[maxn][maxn];

int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> H >> W;
    queue<pair<int,int>> q;
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '#') {
                q.push({i,j});
                dist[i][j] = 0;
            }
            else dist[i][j] = 999999;
        }
    }
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        int x = p.first;
        int y = p.second;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (1 <= nx && nx <= H && 1 <= ny && ny <= W) {
                if (dist[nx][ny] > dist[x][y] + 1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx,ny});
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            ans = max(ans,dist[i][j]);
        }
    }
    cout << ans << '\n';
}

