#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 300;
int grid[maxn][maxn];
int dist[maxn][maxn];
int olddist[maxn][maxn];

int dxx[] = {-1,0,1,0};
int dyy[] = {0,1,0,-1};

int manhat(pair<int,int> a, pair<int,int> b) {
    return abs(a.first-b.first) + abs(a.second-b.second);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        //cout << "test case " << q << '\n';
        memset(grid,0,sizeof grid);
        memset(dist,0,sizeof dist);
        memset(olddist,0,sizeof olddist);
        int R, C; cin >> R >> C;
        vector<pair<int,int>> v;
        queue<pair<int,int>> qu;
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                char c; cin >> c;
                int d = c - '0';
                grid[i][j] = d;
                if (grid[i][j] == 1) {
                    qu.push({i,j});
                    v.push_back({i,j});
                    dist[i][j] = 0;
                }
                else dist[i][j] = 999999;
                olddist[i][j] = dist[i][j];
            }
        }
        int ans = 999999;
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                vector<pair<int,int>> vv = v;
                vv.push_back({i,j});
                int maxdist = 0;
                for (int ii = 1; ii <= R; ii++) {
                    for (int jj = 1; jj <= C; jj++) {
                        dist[ii][jj] = olddist[ii][jj];
                        for (auto p: vv) {
                            dist[ii][jj] = min(dist[ii][jj],manhat(p,{ii,jj}));
                        }
                        maxdist = max(maxdist,dist[ii][jj]);
                    }
                }
                ans = min(ans,maxdist);
            }
        }
        cout << "Case #" << q << ": " << ans << '\n';
    }
}

