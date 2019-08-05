#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int n;
char grid[maxn][maxn];

int parent[maxn*maxn];
int Find(int x) {
    return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return;
    if (parent[x] > parent[y]) swap(x,y);
    parent[x] += parent[y];
    parent[y] = x;
}
int sz(int x) {
    return -parent[sz];
}

int t(int x, int y) {
    return x*n+y;
}
bool valid(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(parent,-1,sizeof parent);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'A') continue;
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k];
                int ny = i + dy[k];
                if (!valid(nx,ny)) continue;
                if (grid[nx][ny] == 'B') {
                    Union(t(i,j),t(nx,ny));
                }
            }
        }
    }
    for (int x1 = 0; x1 < n; x1++) {
        for (int y1 = 0; y1 < n; y1++) {
            if (grid[x1][y1] == 'B') continue;
            for (int x2 = 0; x2 < n; x2++) {
                for (int y2 = 0; y2 < n; y2++) {
                    if (grid[x2][y2] == 'B') continue;
                    vector<int> v;
                    
                }
            }
        }
    }
}

