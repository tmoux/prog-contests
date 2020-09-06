#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
int N, M;
int g[maxn][maxn];
int lowest[maxn][maxn];
bool vis[maxn][maxn];

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
bool valid(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
}

int ans[maxn][maxn];

pair<int,int> par[maxn][maxn];
vector<pair<int,int>> biggest[maxn][maxn];
pair<int,int> getPar(int i, int j) {
    if (par[i][j].first == -1) {
        return {i,j};
    }
    else return par[i][j] = getPar(par[i][j].first,par[i][j].second);
}

int getBiggest(pair<int,int> d) {
    auto p = biggest[d.first][d.second].back();
    return g[p.first][p.second];
}

void Merge(int i, int j, int ni, int nj, int cur) {
    auto pa = getPar(i,j), pb = getPar(ni,nj);
    if (pa == pb) return;
    int ba = getBiggest(pa), bb = getBiggest(pb);
    if (ba < bb) {
        for (auto x: biggest[pa.first][pa.second]) {
            ans[x.first][x.second] = max(0,g[x.first][x.second]-cur);
        }
        biggest[pa.first][pa.second].clear();
    }
    else if (ba > bb) {
        for (auto x: biggest[pb.first][pb.second]) {
            ans[x.first][x.second] = max(0,g[x.first][x.second]-cur);
        }
        biggest[pb.first][pb.second].clear();
    }
    if (biggest[pa.first][pa.second].size() < biggest[pb.first][pb.second].size()) swap(pa,pb);
    for (auto x: biggest[pb.first][pb.second]) {
        biggest[pa.first][pa.second].push_back(x);
    }
    par[pb.first][pb.second] = pa;
}

vector<pair<int,int>> mp[maxn*maxn];

int main() {
    cin >> N >> M;
    //scanf("%d %d",&N,&M);
    int mx = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> g[i][j];
            //scanf("%d",&g[i][j]);

            mp[g[i][j]].push_back({i,j});
            mx = max(mx,g[i][j]);
            par[i][j] = {-1,-1};
            biggest[i][j].push_back({i,j});
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (g[i][j] == mx) ans[i][j] = g[i][j];
        }
    }
    for (int x = mx; x >= 0; x--) {
        for (auto p: mp[x]) {
            int i = p.first;
            int j = p.second;
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (!valid(ni,nj)) continue;
                if (g[ni][nj] >= x) 
                    Merge(i,j,ni,nj,x);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << ans[i][j] << ' ';
            //printf("%d ",ans[i][j]);
        }
        cout << '\n';
        //printf("\n");
    }
}
