#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55;
int r, c;
char grid[maxn][maxn];
pair<int,int> adj[maxn][maxn][4];
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
string s;

bool valid(int i, int j) {
    return 0 <= i && i < r && 0 <= j && j < c;
}
struct State
{
    int i, j, s;    
};

int dist[maxn][maxn][10005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> grid[i][j];
        }
    }
    cin >> s;
    s += '*';
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                while (valid(ni,nj) && grid[ni][nj] == grid[i][j]) {
                    ni += dx[k];
                    nj += dy[k];
                }
                if (!valid(ni,nj)) adj[i][j][k] = {i,j};
                else adj[i][j][k] = {ni,nj};
            }
        }
    }
    queue<State> q;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            for (int k = 0; k < 10005; k++) {
                dist[i][j][k] = 2e9;
            }
        }
    }
    q.push({0,0,0});
    dist[0][0][0] = 0;
    while (!q.empty()) {
        auto f = q.front(); q.pop();
        if (f.s == s.size()) {
            cout << dist[f.i][f.j][f.s] << '\n';
            return 0;
        }
        for (int k = 0; k < 4; k++) {
            int ni = adj[f.i][f.j][k].first;
            int nj = adj[f.i][f.j][k].second;
            if (dist[ni][nj][f.s] > dist[f.i][f.j][f.s] + 1) {
                dist[ni][nj][f.s] = dist[f.i][f.j][f.s] + 1;
                q.push({ni,nj,f.s});
            }
        }
        if (s[f.s] == grid[f.i][f.j]) {
            if (dist[f.i][f.j][f.s+1] > dist[f.i][f.j][f.s] + 1) {
                dist[f.i][f.j][f.s+1] = dist[f.i][f.j][f.s] + 1;
                q.push({f.i,f.j,f.s+1});
            }
        }
    }
}

