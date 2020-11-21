#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
char grid[maxn][maxn];
int N, M;

int ans = 0;
bool vis[maxn][maxn];

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
bool valid(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
}
void dfs(int i, int j) {
    vis[i][j] = true;
    for (int k = 0; k < 4; k++) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (!valid(ni,nj) || grid[ni][nj] == '#' || vis[ni][nj]) continue;
        dfs(ni,nj);
    }
}

int main() {
    int tc = 0;
    while (cin >> N >> M) {
        tc++;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> grid[i][j];
            }
        }
        
        memset(vis,0,sizeof vis);
        ans = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (vis[i][j] || grid[i][j] == '#') continue;
                ans++;
                dfs(i,j);
            }
        }

        printf("Case %d: %d\n",tc,ans);
    }
}
