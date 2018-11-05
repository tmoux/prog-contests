#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 505, maxk = 19;
int n, m;
struct Edge
{
	int from, to, weight, id;
	bool operator<(const Edge& r) {
		return weight < r.weight;
	}
};
vector<Edge> adj[maxn];

int parent[maxn];
int Find(int x) {
	return parent[x] < 0 ? x : parent[x] = Find(parent[x]);
}
void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	if (x == y) return;
	if (parent[x] > parent[y]) swap(x,y);
	parent[x] += parent[y];
	parent[y] = x;
}

int ans[maxn];

int par[maxk][maxn], mx[maxk][maxn], depth[maxn];
void dfs(int i, int p, int d) {
    depth[i] = d;
    for (Edge& e: adj[i]) {
        if (e.to == i) swap(e.from,e.to);
        if (e.to == p) continue;
        //cout << i << ' ' << e.to << ' ' << e.weight << '\n';
        par[0][e.to] = i;
        mx[0][e.to] = e.weight;
        dfs(e.to,i,d+1);
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u,v);
    for (int k = maxk-1; k >= 0; k--) {
        int vv = par[k][v];
        if (vv != -1 && depth[vv] >= depth[u]) {
            v = vv;    
        }
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

int getmx(int u, int lc) {
    int res = 0;
    for (int k = maxk-1; k >= 0; k--) {
        int uu = par[k][u];
        if (uu != -1 && depth[uu] >= depth[lc]) {
            res = max(res,mx[k][u]);
            u = uu;
        }
    }
    return res;
}

int maxpath(int u, int v) {
    int lc = lca(u,v);
    return max(getmx(u,lc),getmx(v,lc));
}

int main()
{
    memset(parent,-1,sizeof parent);
    memset(par,-1,sizeof par);
    scanf("%d %d",&n,&m);
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
    	int u, v, w; scanf("%d %d %d",&u,&v,&w);
    	edges[i] = {u,v,w,i};
    }
   	sort(edges.begin(),edges.end());
   	//build mst
   	vector<Edge> mstEdges;
    vector<bool> isMst(m);
   	int mstWeight = 0;
   	for (int i = 0; i < m; i++) {
   		int u = edges[i].from;
   		int v = edges[i].to;
   		if (Find(u) == Find(v)) continue;
   		Union(u,v);
   		mstEdges.emplace_back(edges[i]);
   		mstWeight += edges[i].weight;	
        isMst[i] = true;
   	}
    //root mst
   	for (Edge& e: mstEdges) {
        adj[e.from].emplace_back(e);
        adj[e.to].emplace_back(e);
   	}
    dfs(1,1,0);
    for (int k = 1; k < maxk; k++) {
        for (int i = 1; i <= n; i++) {
            if (par[k-1][i] == -1) {
                par[k][i] = -1;
            }
            else {
                par[k][i] = par[k-1][par[k-1][i]];
                mx[k][i] = max(mx[k-1][i],mx[k-1][par[k-1][i]]);
            }
        }
    }

    int min2 = 987654321;
    for (int i = 0; i < m; i++) {
        if (isMst[i]) continue;
        Edge e = edges[i];
        int w = maxpath(e.from,e.to);
        min2 = min(min2,mstWeight - w + e.weight);
    }

    printf("Cost: %d\nCost: %d\n",mstWeight,min2==987654321?-1:min2);


    return 0;
}
