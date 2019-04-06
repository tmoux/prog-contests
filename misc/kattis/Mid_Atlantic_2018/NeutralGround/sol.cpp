#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2000;
const int INF = 987654321;
int w, h;
int grid[45][45];
struct FF
{
    int cap[maxn][maxn];
    bool visited[maxn];
    int source, sink;
    FF(string a, string b) {
        N = a.size();
        M = b.size();
        source = N + M;
        sink = source + 1;
        //fill with zeros
        memset(cap,0,sizeof(cap));
        memset(visited,false,sizeof(visited));
        //[0,N) is side 1, [N,M) is side 2, N+M is source, N+M+1 is sink
        for (int i = 0; i < N; i++) {
            for (int j = N; j < N+M; j++) {
                if (abs(a[i] - b[j-N]) >= 3) {
                    cap[i][j] = 1;
                }
            }
        }
        //add source->side 1, side 2 -> sink
        for (int i = 0; i < N; i++) {
            cap[source][i] = 1;
        }
        for (int j = N; j < N + M; j++) {
            cap[j][sink] = 1;
        }
    }

    int dfs(int i, int bneck) {
        if (i == sink) {
            return bneck;
        }
        if (visited[i]) return 0;
        visited[i] = true;
        for (int j = 0; j <= sink; j++) {
            if (cap[i][j] > 0) {
                int f = dfs(j,min(bneck,cap[i][j]));
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

    int getflow() {
        int flow = 0;
        while (true) {
            memset(visited,false,sizeof(visited));
            int f = dfs(source,INF);
            if (f == 0) break;
            flow += f;
        }
        return flow;
    }
};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> w >> h;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char c; cin >> c;
            if ('0' <= c && c <= '9') grid[i][j] = c-'0';
            else if (c == 'A') grid[i][j] = -1;
            else if (c == 'B') grid[i][j] == -2;
        }
    }
}

