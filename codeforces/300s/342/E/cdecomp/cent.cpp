#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5, INF = 987654321;
int n, m, sub_size[maxn];
vector<int> adj[maxn];
struct cent_node
{
	int parent, mn;
	map<int,int> dist;
	cent_node() : mn(INF), parent(0) {}
} cent[maxn];
bool blocked[maxn];

int dfs_size(int i, int p) {
	sub_size[i] = 1;
	for (int j: adj[i]) {
		if (j == p || blocked[j]) continue;
		sub_size[i] += dfs_size(j,i);
	}
	return sub_size[i];
}

int get_centroid(int i, int p, int compSize) {
	for (int j: adj[i]) {
		if (j == p || blocked[j]) continue;
		if (sub_size[j] * 2 > compSize) return get_centroid(j,i,compSize);
	}
	return i;
}

void getDist(int i, int p, int d, map<int,int>& mp) {
	mp[i] = d;
	for (int j: adj[i]) {
		if (j == p || blocked[j]) continue;
		getDist(j,i,d+1,mp);
	}
}

int decomp(int i) {
	int compSize = dfs_size(i,i);
	int centroid = get_centroid(i,i,compSize);
	getDist(centroid,centroid,0,cent[centroid].dist);
	blocked[centroid] = true;
	for (int j: adj[centroid]) {
		if (blocked[j]) continue;
		int c = decomp(j);
		cent[c].parent = centroid;
	}
	
	return centroid;
}

void update(int v, int t) {
	if (v == 0) return;
	cent[v].mn = min(cent[v].mn,cent[v].dist[t]);
	update(cent[v].parent,t);
}

int query(int v, int t) {
	if (v == 0) return INF;
	return min(cent[v].dist[t]+cent[v].mn,query(cent[v].parent,t));
}

int main()
{
    scanf("%d %d",&n,&m);
    for (int i = 0; i < n - 1; i++) {
    	int a, b; scanf("%d %d",&a,&b);
    	adj[a].push_back(b);
    	adj[b].push_back(a);
    }
    decomp(1);
    update(1,1);
    for (int i = 0; i < m; i++) {
    	int t, v; scanf("%d %d",&t,&v);
    	if (t == 1) update(v,v);
    	else printf("%d\n",query(v,v));
    }
    return 0;
}