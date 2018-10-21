#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 55;
char grid[maxn][maxn];
int R, C;

struct State {
    int x, y, dir, dist;
};
bool vis[maxn][maxn][4];
int dp[maxn][maxn][4];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> R >> C;
    queue<State> q;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'N') {
                q.push({i,j,0,0});
            }
            else if (grid[i][j] == 'E') {
                q.push({i,j,1,0});
            }
            else if (grid[i][j] == 'S') {
                q.push({i,j,2,0});
            }
            else if (grid[i][j] == 'W') {
                q.push({i,j,3,0});
            }
        }
    }
    int dx[] = {-1,0,1,0};
    int dy[] = {0,1,0,-1};
    while (!q.empty()) {
        State f = q.front();
        //cout << f.x << ' ' << f.y << ' ' << f.dir << '\n';
        vis[f.x][f.y][f.dir] = true;
        //check if border
        if (f.x == 0 || f.x == R - 1 || f.y == 0 || f.y == C - 1) {
            cout << f.dist << '\n';
            return 0;
        }
        for (int i = -1; i <= 1; i+=2) {
            int nd = (f.dir+4+i)%4;
            if (!vis[f.x][f.y][nd]) {
                vis[f.x][f.y][nd] = true;
                q.push({f.x,f.y,nd,f.dist+1});
            }
        }
        //try going forward
        for (int i = 1;; i++) {
            int nx = f.x + i*dx[f.dir];
            int ny = f.y + i*dy[f.dir];
            if (grid[nx][ny] == 'X' || !(0 <= nx && nx < R && 0 <= ny && ny < C)) {
                break;
            }
            if (!vis[nx][ny][f.dir]) {
                vis[nx][ny][f.dir] = true;
                q.push({nx,ny,f.dir,f.dist});
            }
        }
        q.pop();
    }
    cout << -1 << '\n';
    
    

    return 0;
}
	

