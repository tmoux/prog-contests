#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//draw bipartite graph between x's and y's
//Then each edge is a coordinate, and we want the
//minimum vertex cover, since each edge, we must take 
//at least one of its row or column.
//Then minimum (weighted) vertex cover on 
//bipartite graph is equivalent to 
//max-matching --> max flow.

int n, m;
struct Rect
{
    int x1, y1, x2, y2;
} recs[55];

const int maxn = 205;
const int INF = 2e9+9;
map<int,int> mpX, mpY;
int lenX[maxn], lenY[maxn];
struct FF
{
	int cap[maxn][maxn];
	bool visited[maxn];
	int N, M;
	int source, sink;
	FF(int ptx, int pty) {
		N = ptx, M = pty; //x: [0,ptx-1], y: [ptx,ptx+pty-1]
		source = N + M;
		sink = source + 1;
		memset(cap,0,sizeof(cap));
        for (int i = 0; i < m; i++) {
            //printf("%d: %d, %d: %d\n",recs[i].x1,mpX[recs[i].x1],recs[i].x2,mpX[recs[i].x2]);
            for (int x = mpX[recs[i].x1]; x < mpX[recs[i].x2]; x++) {
                for (int y = mpY[recs[i].y1]; y < mpY[recs[i].y2]; y++) {
                    cap[x][y+ptx] = INF;
                }
            }
        }
        for (int i = 0; i < N; i++) {
            cap[source][i] = lenX[i];
        }
        for (int i = 0; i < M; i++) {
            cap[i+N][sink] = lenY[i];
        }

        /*
        for (int i = 0; i <= sink; i++) {
            for (int j = 0; j <= sink; j++) {
                cout << cap[i][j] << ' ';
            }
            cout << '\n';
        }
        */
	}

	int dfs(int i, int bneck) {
		if (i == sink) return bneck;
		if (visited[i]) return 0;
		visited[i] = true;
		for (int j = 0; j <= sink; j++) {
			if (cap[i][j] > 0) {
				int f = dfs(j,min(bneck,cap[i][j]));
				if (f > 0) {
					//update
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
			flow += f;
			if (f == 0) return flow;
		}
	}
};

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    int ptx = 0, pty = 0;
    vector<int> xs, ys;
    for (int i = 0; i < m; i++) {
        cin >> recs[i].x1 >> recs[i].y1 >> recs[i].x2 >> recs[i].y2;
        recs[i].x2++;
        recs[i].y2++;
        xs.push_back(recs[i].x1);
        xs.push_back(recs[i].x2);
        ys.push_back(recs[i].y1);
        ys.push_back(recs[i].y2);
    }
    xs.push_back(1000000001);
    ys.push_back(1000000001);
    sort(xs.begin(),xs.end());
    xs.erase(unique(xs.begin(),xs.end()),xs.end());
    sort(ys.begin(),ys.end());
    ys.erase(unique(ys.begin(),ys.end()),ys.end());
    sort(xs.begin(),xs.end());
    int last = -1;
    for (int x: xs) {
        if (last != -1) {
            lenX[ptx] = x - last;
            //cout << last << ' ' << lenX[ptx] << '\n';
            mpX[last] = ptx++;
            //cout << last << ' ' << mpX[last] << '\n';
        }
        last = x;
    }
    last = -1;
    for (int y: ys) {
        if (last != -1) {
            lenY[pty] = y - last;
            //cout << last << ' ' << lenY[pty] << '\n';
            mpY[last] = pty++;
        }
        last = y;
    }
    FF graph(ptx,pty);
    cout << graph.getflow() << '\n';
}

