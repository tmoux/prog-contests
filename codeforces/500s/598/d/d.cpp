#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n, m, k;
char grid[maxn][maxn];

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

bool valid(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

int comp[maxn][maxn];
int cnt[maxn*maxn];

void dfs(int i, int j, int pt) {
    comp[i][j] = pt;
    for (int K = 0; K < 4; K++) {
        int ni = i + dx[K];
        int nj = j + dy[K];
        if (!valid(ni,nj)) continue;
        if (grid[ni][nj] == '*') continue;
        if (comp[ni][nj] == 0) {
            dfs(ni,nj,pt);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int pt = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '*') continue;
            if (comp[i][j] == 0) {
                dfs(i,j,pt++);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '*') continue;
            int ans = 0;
            for (int K = 0; K < 4; K++) {
                int ni = i + dx[K];
                int nj = j + dy[K];
                if (!valid(ni,nj)) continue;
                if (grid[ni][nj] == '*') ans++;
            }
            cnt[comp[i][j]] += ans;
        }
    }
    while (k--) {
        int x, y; cin >> x >> y;
        x--; y--;
        cout << cnt[comp[x][y]] << '\n';
    }
}

