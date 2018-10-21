#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e3+5, INF = 1e8;
int n, m;
char grid[maxn][maxn];
map<char,char> nxt = {{'D','I'},{'I','M'},{'M','A'},{'A','D'}};
bool vis[maxn][maxn], onStack[maxn][maxn];
int ans[maxn][maxn];
int dx[4] = {0,1,0,-1}, dy[4] = {-1,0,1,0};

int dfs(int i, int j) {
    //cout << i << ' ' << j << '\n';
    if (onStack[i][j]) {
        vis[i][j] = true;
        return INF;
    }
    if (vis[i][j]) {
        vis[i][j] = true;
        return ans[i][j];
    }
    onStack[i][j] = true;
    if (grid[i][j] == 'A') ans[i][j]++;
    int add = 0;
    for (int a = 0; a < 4; a++) {
        int nx = i + dx[a], ny = j + dy[a];
        if (0 <= nx && nx < n && 0 <= ny && ny < m && grid[nx][ny] == nxt[grid[i][j]]) {
            //cout << i << ' ' << j << ": " << nx << ' ' << ny << '\n';
            add = max(add,dfs(nx,ny));    
        }
    }
    ans[i][j] += add;
    onStack[i][j] = false;
    vis[i][j] = true;
    return ans[i][j];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            grid[i][j] = s[j];
        }
    }

    int maxans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'D') {
                int asdf = dfs(i,j);
                maxans = max(maxans,asdf);
                if (asdf >= INF) {
                    //cout << i << ' ' << j << ' ' << asdf << '\n';
                    cout << "Poor Inna!\n";
                    return 0;
                }
            }
        }
    }

    if (maxans == 0) {
        cout << "Poor Dima!" << '\n';
    }
    else {
        cout << maxans << '\n';
    }


    return 0;
}
	

