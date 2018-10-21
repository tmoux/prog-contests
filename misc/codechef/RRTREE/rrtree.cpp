#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5, maxk = 17, INF = 987654321;
int n=1, m;
vector<int> adj[maxn];
int par[maxk][maxn], depth[maxn];
int queries[maxn];

void dfs(int i, int p, int d) {
	depth[i] = d;
	par[0][i] = p;
	for (int j: adj[i]) {
		if (j == p) continue;
		dfs(j,i,d+1);
	}
}

int lca(int u, int v) {
	if (depth[u] > depth[v]) swap(u,v);
	for (int k = maxk-1; k >= 0; k--) {
		int vv = par[k][v];
		if (vv != -1 && depth[vv] >= depth[u])
			v = vv;
	}
	if (u == v) return u;
	for (int k = maxk-1; k >= 0; k--) {
		int uu = par[k][u], vv = par[k][v];
		if (uu != vv) {
			u = uu;
			v = vv;
		}
	}
	return par[0][u];
}

int dist(int u, int v) {
	int l = lca(u,v);
	return depth[u]+depth[v]-2*depth[l];
}

int l1 = 2, l2 = 4;
int diam = 2;

void update(int v) {
	int d = dist(v,l1);
	if (d > diam) {
		diam = d;
		l2 = v;
	}
	else {
		d = dist(v,l2);
		if (d > diam) {
			diam = d;
			l1 = v;
		}
	}
}

int main()
{
	//start with tree
	int t; scanf("%d",&t);
	while (t--) {
	    scanf("%d",&m);
	    n = m;
	    l1 = 1;
	    l2 = 1;
	    diam = 0;
	    for (int i = 1; i <= n; i++) {
	    	adj[i].clear();
	    }
	    memset(par,-1,sizeof par);
	    memset(depth,-1,sizeof depth);
	    for (int i = 2; i <= n; i++) {
	    	int v; scanf("%d",&v);
	    	adj[i].push_back(v);
	    	adj[v].push_back(i);
	    	queries[i] = i;
	    }
	    dfs(1,-1,0);
	    for (int k = 1; k < maxk; k++) {
	    	for (int i = 1; i <= n; i++) {
	    		if (par[k-1][i] == -1) par[k][i] = -1;
	    		else par[k][i] = par[k-1][par[k-1][i]];
	    	}
	    }
	    
	    for (int i = 2; i <= m; i++) {
	    	update(i);
	    	cout << diam << '\n';
	    }
	}
    return 0;
}