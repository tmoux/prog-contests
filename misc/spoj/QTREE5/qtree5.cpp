#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5, INF = 987654321;
int n, m, sub_size[maxn];
vector<int> adj[maxn];
struct cent_node
{
	int parent;
	unordered_map<int,int> dist;
	multiset<int> ms;
	bool active;
	cent_node() : parent(0), active(false) {}
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

void getDist(int i, int p, int d, unordered_map<int,int>& mp) {
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


void updateWhite(int v, int t) {
	if (v == 0) return;
    cent[v].ms.insert(cent[v].dist[t]);
	updateWhite(cent[v].parent,t);
}

void updateBlack(int v, int t) {
	if (v == 0) return;
	auto it = cent[v].ms.find(cent[v].dist[t]);
	cent[v].ms.erase(it);
	updateBlack(cent[v].parent,t);
}

inline int minElement(multiset<int>& ms) {
	return ms.empty() ? INF : *ms.begin();
}

int query(int v, int t) {
	if (v == 0) return INF;
	return min(cent[v].dist[t]+minElement(cent[v].ms),query(cent[v].parent,t));
}

int main()
{
    scanf("%d",&n);
    for (int i = 0; i < n - 1; i++) {
    	int a, b; scanf("%d %d",&a,&b);
    	adj[a].push_back(b);
    	adj[b].push_back(a);
    }
    decomp(1);
    scanf("%d",&m);
    while (m--) {
    	int t, v; scanf("%d %d",&t,&v);
    	if (t == 0) {
    		if (cent[v].active == false) {
    			cent[v].active = true;
    			updateWhite(v,v);
    		}
    		else {
    			cent[v].active = false;
    			updateBlack(v,v);
    		}
    	}
    	else {
    		int ans = query(v,v);
    		cout << (ans == INF ? -1 : ans) << '\n';
    	}
    }

    return 0;
}
