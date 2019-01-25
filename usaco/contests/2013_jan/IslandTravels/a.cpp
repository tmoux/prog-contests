#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pp = pair<pair<int,int>,int>;

const int maxn = 55, INF = 999999;
int R, C;
char grid[maxn][maxn];
int compLabel[maxn][maxn];
bool vis[maxn][maxn];
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
bool valid(int i, int j) {
    return 0 <= i && i < R && 0 <= j && j < C; 
}

void mark(int i, int j, int comp) {
    compLabel[i][j] = comp;
    for (int k = 0; k < 4; k++) {
        int nx = i + dx[k];
        int ny = j + dy[k];
        if (!valid(nx,ny)) continue;
        if (grid[nx][ny] == 'X' && compLabel[nx][ny] == 0) {
            mark(nx,ny,comp);
        }
    }
}

int dist[maxn][maxn];

class comp
{
public:
    bool operator() (const pp& a, const pp& b) const {
        return a.second > b.second;        
    }
};

void fillDist(int c) {
    priority_queue<pp,vector<pp>,comp> q;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (compLabel[i][j] == c) {
                q.push({{i,j},0});
                vis[i][j] = true;
            }
        }
    }
    while (!q.empty()) {
        auto f = q.top(); q.pop();
        int x = f.first.first;
        int y = f.first.second;
        int d = f.second;
        //printf("comp #%d: (%d,%d), dist = %d\n",c,x,y,d);
        if (grid[x][y] == 'X') {
            int o = compLabel[x][y];
            dist[c][o] = min(dist[c][o],d);
            dist[o][c] = min(dist[o][c],d);
        }
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            //cout << nx << ' ' << ny << ": " << vis[nx][ny] << '\n';
            if (!valid(nx,ny) || grid[nx][ny] == '.') continue;
            if (grid[nx][ny] == 'X') {
                int o = compLabel[nx][ny];
                dist[c][o] = min(dist[c][o],d);
                dist[o][c] = min(dist[o][c],d);
            }    
            if (vis[nx][ny]) continue;
            vis[nx][ny] = true;
            int nd = (grid[nx][ny] == 'S' ? d+1 : d);
            q.push({{nx,ny},nd});
        }
    }
}

int N;
int dp[18][1<<18];
int f(int i, int mask) {
    if (dp[i][mask] >= 0) return dp[i][mask];
    int cnt = 0;
    for (int j = 1; j <= N; j++) if (mask & (1<<j)) cnt++;
    if (cnt == N) return dp[i][mask] = 0; //done
    dp[i][mask] = INF;
    for (int j = 1; j <= N; j++) {
        if (!(mask & (1<<j))) {
            dp[i][mask] = min(dp[i][mask],f(j,mask|(1<<j)) + dist[i][j]);
        }
    }
    assert(dp[i][mask] != INF);
    return dp[i][mask];
}

int main()
{
    freopen("island.in","r",stdin); freopen("island.out","w",stdout);
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> grid[i][j];
        }
    }
    //label all components
    int comp = 1;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == 'X' && compLabel[i][j] == 0) {
                mark(i,j,comp);
                comp++;
            }
        }
    }
    //now get distances of the graph    
    N = comp-1; //# of components
    assert(N <= 15);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            dist[i][j] = INF;
        }
    }
    for (int i = 1; i <= N; i++) {
        memset(vis,false,sizeof(vis));
        fillDist(i);
    }
    /*
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cout << dist[i][j] << ' ';
        }
        cout << '\n';
    }
    */
    //do tsp
    int ans = INF;
    memset(dp,-1,sizeof dp);
    for (int i = 1; i <= N; i++) {
        ans = min(ans,f(i,1<<i));
    }
    assert(ans < INF);
    cout << ans << '\n';
    return 0;
}

