#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 22;
bool vis[maxn][maxn];

int R, C;
vector<pair<int,int>> st;
bool found = false;

void DFS(int i, int j) {
    if (found) return;
    st.push_back({i,j});
    vis[i][j] = true;
    int cnt = 0;
    for (int x = 0; x < R; x++) {
        for (int y = 0; y < C; y++) 
            if (vis[x][y]) cnt++;
    }
    if (cnt == R*C) {
        found = true;
        return;
    }
    for (int x = 0; x < R; x++) {
        for (int y = 0; y < C; y++) {
            if (i == x || y == j || i-j == x-y || i+j == x+y) {
                continue;
            }
            if (vis[x][y]) continue;
            DFS(x,y);
        }
    }
    if (found) return;
    st.pop_back();
    vis[i][j] = false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        cin >> R >> C;
        found = false;
        st.clear();
        if (R <= 5 && C <= 5) {
            memset(vis, 0, sizeof vis);
            DFS(0,0);
            cout << "Case #" << qq << ": ";
            cout << R << ' ' << C << ": ";
            if (!found) {
                cout << "IMPOSSIBLE\n";
            }
            else {
                cout << "POSSIBLE\n";
                for (auto p: st) {
                    cout << (p.first+1) << ' ' << (p.second+1) << '\n';
                }
            }
        }
        else {
            //must be possible
            vector<pair<int,int>> ans;
            while (true) {
                ans.clear();
                int cnt = 1;
                int px = 1, py = 1;
                memset(vis,0,sizeof vis);
                vis[px][py] = 1;
                while (cnt < R*C) {
                    int x, y;
                    do {
                        x = rand() % R + 1;
                        y = rand() % C + 1;
                    } while (vis[x][y]);
                    if (px==x||py==y||px+py==x+y||px-py==x-y)
                        break;
                    vis[x][y] = 1;
                    cnt++;
                    ans.push_back({x,y});
                    px = x;
                    py = y;
                }
                if (cnt == R*C) {
                    cout << "Case #" << qq << ": POSSIBLE\n";
                    for (auto p: ans) {
                        cout << p.first << ' ' << p.second << '\n';
                    }
                    break;
                }
            }
        }
    }
}

