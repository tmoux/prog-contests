#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 205;
const int INF = 999999999;

struct FF
{
	int cap[maxn][maxn];
	bool visited[maxn];
	int ai[maxn], bi[maxn];
	int N, M;
	int source, sink;
	int asum = 0, bsum = 0;
	FF(int n, int m) {
		N = n, M = n;
		source = N + M;
		sink = source + 1;
		memset(cap,0,sizeof(cap));
		for (int i = 0; i < n; i++) {
			cin >> ai[i];
			asum += ai[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> bi[i];
			bsum += bi[i];
		}
		//build capacity graph
		for (int i = 0; i < N; i++) {
			cap[source][i] = ai[i];
		}
		for (int i = N; i < N + M; i++) {
			cap[i][sink] = bi[i-N];
		}
		for (int i = 0; i < m; i++) {
			int a, b; cin >> a >> b;
			a--; b--;
			cap[a][b+N] = ai[a];
			cap[b][a+N] = ai[b];
		}
		for (int i = 0; i < N; i++) {
			cap[i][i+N] = ai[i];
		}
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
	#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
	#endif
	int n, m; cin >> n >> m;
	FF g(n,m);
	/*
	for (int i = 0; i <= g.sink; i++) {
		for (int j = 0; j <= g.sink; j++) {
			cout << g.cap[i][j] << ' ';
		}
		cout << '\n';
	}
	*/
	if (g.bsum != g.asum || g.getflow() != g.bsum) {
		//not possible
		cout << "NO\n";
		return 0;
	}
	else {
		cout << "YES\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << g.cap[j+n][i] << ' ';
			}
			cout << '\n';
		}
	}
	
	return 0;
	
}