#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
const double INF = 1e32;
int N, M;
struct edge
{
	int to, c, d;
};
vector<edge> adj[maxn];

double dist[maxn][maxn];
bool poss(double mu) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			dist[i][j] = INF;
		}
	}
	for (int i = 1; i <= N; i++) {
		for (edge& e: adj[i]) {
			int b = e.to;
			double d = (1.0*e.c/e.d-mu)*e.d;
			dist[i][b] = min(dist[i][b],d);
		}
	}
	vector<double> mindist(N+1); //min dist to one in minimal spanning tree
	vector<int> tree;
	vector<bool> intree(N+1,false);
	tree.push_back(1);
	intree[1] = true;
	double cost = 0;
	for (int i = 1; i <= N; i++) {
		mindist[i] = dist[1][i];
	}
	while (tree.size() != N) {
		pair<double,int> best = {INF,-1};
		for (int i = 1; i <= N; i++) {
			if (intree[i]) continue;
			best = min(best,{mindist[i],i});
		}
		assert(best.second != -1);
		cost += best.first;
		tree.push_back(best.second);
		intree[best.second] = true;
		for (int i = 1; i <= N; i++) {
			mindist[i] = min(mindist[i],dist[i][best.second]);
		}
	}
	return cost <= 0;
}

int main()
{
	//freopen("in","r",stdin);
	scanf("%d %d",&N,&M);
	for (int i = 0; i < M; i++) {
		int a, b, c, d;
		scanf("%d %d %d %d",&a,&b,&d,&c);
		adj[a].push_back({b,c,d});
		adj[b].push_back({a,c,d});
	}

	double lo = 0, hi = 1e7;
	for (int i = 0; i < 50; i++) {
		double m = (lo+hi)/2;
		if (poss(m)) {
			hi = m;
		}
		else lo = m;
	}
	printf("%.10f\n",hi);
	
	return 0;
}