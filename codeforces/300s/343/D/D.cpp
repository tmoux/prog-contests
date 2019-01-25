#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5+5;
const ll NEG = -1e18;
int n, q;

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll lazy;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = -1;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m);
			r = new Node(m+1,e);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}

	void push() {
		if (lazy == -1) return;
		if (s != e) {
			l->lazy = lazy;
			l->sum = (l->e - l->s + 1) * lazy;

			r->lazy = lazy;
			r->sum = (r->e - r->s + 1) * lazy;
		}
		lazy = -1;
	}

	void pull() {
		sum = l->sum + r->sum;
	}

	void add(int st, int en, ll x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy = x;
			sum = (e - s + 1) * x;
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		pull();
	}

	ll getsum(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return sum;
		}
		ll ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};

namespace HLD
{
	int preorder[maxn], postorder[maxn], sub_size[maxn], weight[maxn], real_to_hld[maxn];
	int pre = 0, hld_id = 1;
	vector<int> adj[maxn];
	struct node {
		int parent, lastPrev, _preorder, _postorder, realid, lastHLD;
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
		nodes[id].realid = i;
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
			if (sub_size[j] * 2 > sub_size[i]) hld(j,i,false);
		}
		for (int j: adj[i]) {
			if (j == par) continue;
			if (sub_size[j] * 2 <= sub_size[i]) hld(j,i,true);
		}
		nodes[id].lastHLD = hld_id-1;
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
};
using namespace HLD;

void removeAncestors(int u, Node *seg) {
	while (true) {
		seg->add(nodes[u].parent,u,0);
		if (nodes[u].lastPrev == u) break; //top chain
		u = nodes[u].lastPrev;
	}
}

int main()
{
	//freopen("in","r",stdin);
    scanf("%d",&n);
	for (int i = 0; i < n - 1; i++) {
		int a, b; scanf("%d %d",&a,&b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs_prep(1,1);
	hld(1,1,1);
	Node *seg = new Node(1,n);
	scanf("%d",&q);
	while (q--) {
		int t, v; scanf("%d %d",&t,&v);
		int u = real_to_hld[v];
		if (t == 1) {
			//fill children
			seg->add(u,nodes[u].lastHLD,1);
		}
		else if (t == 2) {
			removeAncestors(u,seg);
		}
		else {
			int ans = seg->getsum(u,u);
			printf("%d\n",ans);
		}
	}	
	
	
	
	
	
	
	
    return 0;
}