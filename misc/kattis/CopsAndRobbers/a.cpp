#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 31*31;
int n, m, c;
char grid[33][33];
int cost[30];

const ll INF = 1LL<<50;

int dx[] = {0,-1,0,1};
int dy[] = {1,0,-1,0};

ll cap[2*maxn][2*maxn];
bool visited[2*maxn];

struct FF
{
    ll source, sink;
    bool valid(int i, int j) {
        return 0 <= i && i < m && 0 <= j && j < n;
    }
    int cv(int i, int j) {
        return i*n + j;
    }
    FF(pair<int,int> p) {
        source = cv(p.first,p.second);
        sink = 2*n*m;
        //fill with zeros
        memset(cap,0,sizeof(cap));
        memset(visited,false,sizeof(visited));
        //add edges
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                //add in -> out. INF if B or . else cost[char]
                if (grid[i][j] == '.' || grid[i][j] == 'B') {
                    cap[cv(i,j)][cv(i,j)+n*m] = INF;
                }
                else {
                    cap[cv(i,j)][cv(i,j)+n*m] = cost[grid[i][j]-'a'];
                }
                //add out -> adjacent (in)
                for (int k = 0; k < 4; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (valid(ni,nj)) {
                        cap[cv(i,j)+n*m][cv(ni,nj)] = INF;
                    }
                }
                //connect boundaries to sink
                if (i == 0 || i == m-1 || j == 0 || j == n-1) {
                    cap[cv(i,j)+n*m][sink] = INF;
                }
            }
        }
    }

    ll dfs(ll i, ll bneck) {
        if (i == sink) {
            return bneck;
        }
        if (visited[i]) return 0;
        visited[i] = true;
        for (int j = 0; j <= sink; j++) {
            if (cap[i][j] > 0) {
                ll f = dfs(j,min(bneck,cap[i][j]));
                if (f > 0) {
                    //update, recurse upwards
                    cap[i][j] -= f;
                    cap[j][i] += f;
                    return f;
                }
            }
        }
        return 0;
    }

    ll getflow() {
        ll flow = 0;
        while (true) {
            memset(visited,false,sizeof(visited));
            ll f = dfs(source,INF);
            if (f == 0) break;
            flow += f;
        }
        return flow;
    }
};

int main() {
    cin >> n >> m >> c;
    pair<int,int> start;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'B') {
                start = {i,j};
            }
        }
    }
    for (int i = 0; i < c; i++) {
        cin >> cost[i];
    }
    FF graph = FF(start);
    ll ans = graph.getflow();
    cout << (ans >= INF ? -1 : ans) << '\n';
}

