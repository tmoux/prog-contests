#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 55;
int n;
bool isLand[maxn][maxn], vis[maxn][maxn];
int component[maxn][maxn];
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

void FILL(int i, int j, int comp) {
    vis[i][j] = true;
    component[i][j] = comp;
    for (int a = 0; a < 4; a++) {
        int ni = i + dx[a];
        int nj = j + dy[a];
        if (1 <= ni && ni <= n && 1 <= nj && nj <= n) {
            if (!vis[ni][nj] && isLand[ni][nj]) {
                vis[ni][nj] = true;
                FILL(ni,nj,comp);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    pair<int,int> source; cin >> source.first >> source.second;
    pair<int,int> sink; cin >> sink.first >> sink.second;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char ai; cin >> ai;
            isLand[i][j] = ai == '0';
        }
    }
    //flood fill
    int comp = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (isLand[i][j] && !vis[i][j]) {
                FILL(i,j,comp);
                comp++;
            }
        }
    }
    /*
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << component[i][j] << ' ';
        }
        cout << '\n';
    }
    */
    int c1 = component[source.first][source.second];
    int c2 = component[sink.first][sink.second];

    int ans = 2e9;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (component[i][j] == c1) {
                //cout << i << ' ' << j << '\n';
                for (int a = 1; a <= n; a++) {
                    for (int b = 1; b <= n; b++) {
                        if (component[a][b] == c2) {
                            int cost = (i-a)*(i-a) + (j-b)*(j-b);
                            ans = min(ans,cost);
                            //cout << i << ' ' << j << ' ' << a << ' ' << b << '\n';
                        }
                    }
                }
            }
        }
    }
    cout << ans << '\n';
}

