#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5, INF = 987654321;
int n, m, sub_size[maxn];
vector<int> adj[maxn];
struct cent_node
{
	int parent = 0, mx1 = 0, mx2 = 0, whichtop = -1;
	bool awake = false;
	map<int,int> dist, subtree;

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

void getSub(int i, int p, int j, map<int,int>& mp) {
	mp[i] = j;
	for (int s: adj[i]) {
		if (s == p || blocked[s]) continue;
		getSub(s,i,j,mp);
	}
}

int decomp(int i) {
	int compSize = dfs_size(i,i);
	int centroid = get_centroid(i,i,compSize);
	getDist(centroid,centroid,0,cent[centroid].dist);
	blocked[centroid] = true;
	for (int j: adj[centroid]) {
		if (blocked[j]) continue;
		getSub(j,centroid,j,cent[centroid].subtree);
		int c = decomp(j);
		cent[c].parent = centroid;
	}
	return centroid;
}

void propUp(int v, int t) {
	if (v == 0) return;
	int d = cent[v].dist[t];
	int sub = cent[v].subtree[t];
	if (sub != cent[v].whichtop) {
		if (d > cent[v].mx1) {
			cent[v].mx1 = d;
			cent[v].whichtop = sub;
			if (sub == 0) {
				cout << v << ' ' << t << '\n';
			}
		}
		else if (d > cent[v].mx2) cent[v].mx2 = d;
	}
	else {
		if (d > cent[v].mx1) cent[v].mx1 = d;
	}
	propUp(cent[v].parent,t);
}

void update(int v) {
	cent[v].awake = true;
	propUp(cent[v].parent,v);
}

int query(int v, int t) {
	if (v == 0) return 0;
	if (!cent[v].awake) return query(cent[v].parent,t);
	int d = cent[v].dist[t];
	int l = cent[v].whichtop == cent[v].subtree[t] ? cent[v].mx2 : cent[v].mx1;
	return max(d+l,query(cent[v].parent,t));
}

pair<char,int> queries[maxn];

int main()
{
	freopen("newbarn.in","r",stdin);
	freopen("newbarn.out","w",stdout);
    cin >> m;
    for (int i = 0; i < m; i++) {
    	char c; int v; cin >> c >> v;
    	if (c == 'B') {
			queries[i] = {c,++n};
			if (v != -1) {
				adj[n].push_back(v);
				adj[v].push_back(n);
			}
    	}
    	else queries[i] = {c,v};
    }
    for (int i = 1; i <= n; i++) {
    	if (!blocked[i]) decomp(i);
    }
  
    for (int i = 0; i < m; i++) {
    	char c = queries[i].first;
    	int v = queries[i].second;
    	if (c == 'B') {
    		update(v);
    	}
    	else {
    		int ans = query(v,v);
    		cout << ans << '\n';
    	}
    }
    return 0;
}



