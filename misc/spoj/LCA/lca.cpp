#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10005;
int n, preorder[maxn], postorder[maxn], sub_size[maxn], weight[maxn], real_to_hld[maxn];
int pre = 0, hld_id = 1;
vector<int> adj[maxn];
struct Node {
	int real, parent, lastPrev, _preorder, _postorder;
} nodes[maxn];

int dfs_prep(int i, int par) {
	preorder[i] = pre++;
	sub_size[i] = 1;
	for (int j: adj[i]) {
		if (j == par) continue;
		sub_size[i] += dfs_prep(j,i);
	}
	postorder[i] = pre;
	return sub_size[i];
}

void hld(int i, int par, bool newChain) {
	real_to_hld[i] = hld_id++;
	int id = real_to_hld[i];
	nodes[id]._preorder = preorder[i];
	nodes[id]._postorder = postorder[i];
	nodes[id].real = i;
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
		if (sub_size[j] * 2 >= sub_size[i]) hld(j,i,false);
	}
	for (int j: adj[i]) {
		if (j == par) continue;
		if (sub_size[j] * 2 < sub_size[i]) hld(j,i,true);
	}
}

bool isAncestor(int u, int v) { //whether u is an ancestor of v, hld terms
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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    int t; cin >> t;
    for (int a = 1; a <= t; a++) {
    	cin >> n;
    	//clear everything
        pre = 0, hld_id = 1;
    	for (int i = 1; i <= n; i++) adj[i].clear();

    	for (int i = 1; i <= n; i++) {
    		int m; cin >> m;
    		while (m--) {
    			int ai; cin >> ai;
    			adj[i].push_back(ai);
    			adj[ai].push_back(i);
    		}
    	}
    	dfs_prep(1,1);
    	hld(1,1,true);
    	int q; cin >> q;
    	cout << "Case " << a << ":\n";
    	while (q--) {
    		int u, v; cin >> u >> v;
    		u = real_to_hld[u], v = real_to_hld[v];
    		cout << nodes[lca(u,v)].real << '\n';
    	}
    }

    return 0;
}
