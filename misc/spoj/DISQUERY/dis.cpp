#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5, maxk = 18;
int n, par[maxk][maxn], mx[maxk][maxn], mn[maxk][maxn], depth[maxn];
vector<int> adj[maxn];
map<pair<int,int>,int> edges;

void dfs(int i, int p) {
	for (int j: adj[i]) {
		if (j == p) continue;
		depth[j] = depth[i]+1;
		par[0][j] = i;
		mx[0][j] = edges[{i,j}];
		mn[0][j] = mx[0][j];
		dfs(j,i);
	}
}

int lca(int u, int v) {
	if (depth[u] > depth[v]) swap(u,v);
	for (int k = maxk - 1; k >= 0; k--) {
		int vv = par[k][v];
		if (vv != -1 && depth[vv] >= depth[u]) v = vv;
	}
	if (u == v) return u;
	for (int k = maxk - 1; k >= 0; k--) {
		int uu = par[k][u], vv = par[k][v];
		if (uu != vv) {
			u = uu;
			v = vv;
		}
	}
	return par[0][u];
}

int maxWalk(int u, int v) {
	int res = 0;
	for (int k = maxk - 1; k >= 0; k--) {
		int uu = par[k][u];
		if (uu != -1 && depth[uu] >= depth[v]) {
			res = max(res,mx[k][u]);
			u = uu;
		}
	}
	return res;
}

int minWalk(int u, int v) {
	int res = 1e9;
	for (int k = maxk - 1; k >= 0; k--) {
		int uu = par[k][u];
		if (uu != -1 && depth[uu] >= depth[v]) {
			res = min(res,mn[k][u]);
			u = uu;
		}
	}
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
    	int u, v, w; cin >> u >> v >> w;
    	adj[u].push_back(v);
    	adj[v].push_back(u);
    	edges[{u,v}] = w;
    	edges[{v,u}] = w;
    }
    //prepare tree
    memset(par,-1,sizeof par);
    dfs(1,1);
    //sparse table precomp
    for (int k = 1; k < maxk; k++) {
    	for (int i = 1; i <= n; i++) {
    		if (par[k-1][i] == -1) par[k][i] = -1;
    		else par[k][i] = par[k-1][par[k-1][i]];
    		if (par[k][i] != -1) {
    			mx[k][i] = max(mx[k-1][i],mx[k-1][par[k-1][i]]);
    			mn[k][i] = min(mn[k-1][i],mn[k-1][par[k-1][i]]);
    		}
    	}
    }
    //answer queries
    int q; cin >> q;
    while (q--) {
    	int u, v; cin >> u >> v;
		int lc = lca(u,v);
		int mindist = min(minWalk(u,lc),minWalk(v,lc));
		int maxdist = max(maxWalk(u,lc),maxWalk(v,lc));
		cout << mindist << ' ' << maxdist << '\n';  
    }

    return 0;
}