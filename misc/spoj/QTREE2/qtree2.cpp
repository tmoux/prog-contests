#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10005;
int n, preorder[maxn], postorder[maxn], sub_size[maxn], weight[maxn], real_to_hld[maxn];
int pre = 0, hld_id = 1;
vector<int> adj[maxn];
map<pair<int,int>,pair<int,int>> mp;
struct Node {
	int real, parent, lastPrev, _preorder, _postorder, depth;
} nodes[maxn];

int edge_to_real[maxn];
int dfs_prep(int i, int par) {
	preorder[i] = pre++;
	weight[i] = mp[{i,par}].first;
	edge_to_real[mp[{i,par}].second] = i;
	sub_size[i] = 1;
	for (int j: adj[i]) {
		if (j == par) continue;
		sub_size[i] += dfs_prep(j,i);
	}
	postorder[i] = pre;
	return sub_size[i];
}

int dist[maxn];
int getdist(int l, int r) {
	return dist[r] - dist[l-1];
}
void hld(int i, int par, bool newChain, int dep) {
	real_to_hld[i] = hld_id++;
	
	int id = real_to_hld[i];
	nodes[id]._preorder = preorder[i];
	nodes[id]._postorder = postorder[i];
	nodes[id].depth = dep;
	nodes[id].real = i;
	dist[id] = weight[i];
	if (newChain) {
		nodes[id].parent = id;
		nodes[id].lastPrev = real_to_hld[par]; //lastprev[1] = 1
	}
	else {
		nodes[id].parent = nodes[real_to_hld[par]].parent;
		nodes[id].lastPrev = nodes[real_to_hld[par]].lastPrev;
	}
	for (int j: adj[i]) {
		if (j == par) continue;
		if (sub_size[j] * 2 >= sub_size[i]) hld(j,i,false,dep+1);
	}
	for (int j: adj[i]) {
		if (j == par) continue;
		if (sub_size[j] * 2 < sub_size[i]) hld(j,i,true,dep+1);
	}
}

inline bool isAncestor(int u, int v) { //whether u is an ancestor of v, hld terms
    return nodes[u]._preorder <= nodes[v]._preorder && nodes[v]._preorder < nodes[u]._postorder;   
}

int lca(int u, int v) { //returns lca(u,v) in terms of hld-id's
    while (!isAncestor(nodes[u].parent,v)) {
        u = nodes[u].lastPrev;
    }
    int lo = nodes[u].parent, hi = u;
    if (isAncestor(hi,v)) return hi;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (isAncestor(mid,v)) {
            lo = mid;
        }
        else hi = mid;
    }
    return lo;
}

int query_dist(int u, int lc) {
	int res = 0;
	while (nodes[u].parent != nodes[lc].parent) {
		res += getdist(nodes[u].parent,u);
		u = nodes[u].lastPrev;
	}
	res += getdist(lc+1,u);
	return res;
}

int kth(int u, int k) {
	if (k == 1) return u;
	int mv = nodes[u].depth - nodes[nodes[u].lastPrev].depth;
	if (k - mv >= 1) return kth(nodes[u].lastPrev,k-mv);
	return u - (k-1);
}

int main()
{    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    int t; cin >> t;
    while (t--) {
    	cin >> n;
    	//clear everything
    	memset(dist,0,sizeof(dist));
    	//memset(preorder,0,sizeof(preorder));
    	//memset(postorder,0,sizeof(postorder));
    	//memset(sub_size,0,sizeof(sub_size));
    	//memset(weight,0,sizeof(weight));
    	//memset(weight,0,sizeof(weight));
    	//memset(edge_to_real,0,sizeof(edge_to_real));
        pre = 0, hld_id = 1;
    	//for (int i = 1; i <= n; i++) nodes[i] = {0,0,0,0,0};
    	for (int i = 1; i <= n; i++) adj[i].clear();
    	mp.clear();

    	for (int i = 1; i <= n - 1; i++) {
    		int a, b, c; cin >> a >> b >> c;
    		adj[a].push_back(b);
    		adj[b].push_back(a);
    		mp[{a,b}] = {c,i};
    		mp[{b,a}] = {c,i};
    	}
    	dfs_prep(1,1);
    	hld(1,1,true,0);
    	for (int i = 1; i <= n; i++) {
    		dist[i] += dist[i-1];
    	}
    	//answer queries
    	for (;;) {
    		string s; cin >> s;
    		if (s[1] == 'O') break;
    		else if (s[1] == 'I') { //dist query
    			int u, v; cin >> u >> v;
    			u = real_to_hld[u], v = real_to_hld[v];
    			int lc = lca(u,v);
    			int dist = query_dist(u,lc) + query_dist(v,lc);
    			cout << dist << '\n';
    		}
    		else { //kth query
    			int u, v, k; cin >> u >> v >> k;
    			u = real_to_hld[u], v = real_to_hld[v];
    			int lc = lca(u,v);
    			int ans;
    			int tot = nodes[u].depth + nodes[v].depth - 2 * nodes[lc].depth + 1;
    			k = min(k,tot);
    			if (k <= nodes[u].depth - nodes[lc].depth + 1) {
    				ans = kth(u,k);
    			}
    			else {
    				int d = nodes[v].depth - nodes[lc].depth + 2;
    				k = d - (k - (nodes[u].depth - nodes[lc].depth));
    				ans = kth(v,k);
    			}
    			ans = nodes[ans].real;
    			cout << ans << '\n';
    		}
    	}
    }

    return 0;
}
