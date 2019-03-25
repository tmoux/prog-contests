#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 300;
int grid[maxn][maxn];
int dist[maxn][maxn];

int dxx[] = {-1,0,1,0};
int dyy[] = {0,1,0,-1};

int manhat(pair<int,int> a, pair<int,int> b) {
    return abs(a.first-b.first) + abs(a.second-b.second);
}

int R, C;

bool poss(int k) {
    //returns if possible to have a maximum of <= k
    vector<pair<int,int>> v;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            if (dist[i][j] > k) v.push_back({i,j});
        }
    }
    if (v.empty()) return true;
    pair<int,pair<int,int>> mx1 = {-99999,{-1,-1}}, mx2 = {-99999,{-1,-1}}, mn1 = {99999,{-1,-1}}, mn2 = {99999,{-1,-1}};
    for (auto p: v) {
        mx1 = max(mx1,{p.first+p.second,p});
        mx2 = max(mx2,{p.first-p.second,p});
        mn1 = min(mn1,{p.first+p.second,p});
        mn2 = min(mn2,{p.first-p.second,p});
    }
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            //int d = max(abs(mx.first-(i+j)),abs(mn.first-(i-j)));
            int d = max(manhat({i,j},mx1.second),manhat({i,j},mn1.second));
            d = max(d,max(manhat({i,j},mx2.second),manhat({i,j},mn2.second)));
            if (d <= k) return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        //cout << "test case " << q << '\n';
        memset(grid,0,sizeof grid);
        memset(dist,0,sizeof dist);
        cin >> R >> C;
        queue<pair<int,int>> qu;
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                char c; cin >> c;
                int d = c - '0';
                grid[i][j] = d;
                if (grid[i][j] == 1) {
                    qu.push({i,j});
                    dist[i][j] = 0;
                }
                else dist[i][j] = 999999;
            }
        }
        while (!qu.empty()) {
            auto f = qu.front(); qu.pop();
            int x = f.first;
            int y = f.second;
            for (int i = 0; i < 4; i++) {
                int dx = dxx[i];
                int dy = dyy[i];
                int nx = x + dx;
                int ny = y + dy;
                if (1 <= nx && nx <= R && 1 <= ny && ny <= C) {
                    if (dist[x][y] + 1 < dist[nx][ny]) {
                        dist[nx][ny] = dist[x][y] + 1;
                        qu.push({nx,ny});
                    }
                }
            }
        }
        int lo = -1, hi = R + C + 1;
        while (lo + 1 < hi) {
            int mid = (lo+hi)>>1;
            if (poss(mid)) {
                hi = mid;
            }
            else lo = mid;
        }
        cout << "Case #" << q << ": " << hi << '\n';
    }
}

