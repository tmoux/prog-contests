#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, maxk = 17;
int N, Q; 
int val[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
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

	void add(int i, int x) {
		if (s == e) {
			sum = x;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		sum = l->sum ^ r->sum;
	}

	int getsum(int st, int en) {
		if (st <= s && e <= en) {
			return sum;
		}
		int ret = 0;
		if (st <= m) {
			ret ^= l->getsum(st,en);
		}
		if (en > m) {
			ret ^= r->getsum(st,en);
		}
		return ret;
	}
};

namespace HLD
{
	int preorder[maxn], postorder[maxn], sub_size[maxn], weight[maxn], real_to_hld[maxn], parent[maxn];
	int pre = 0, hld_id = 1;
	vector<int> adj[maxn];
	struct node {
		int parent, lastPrev, _preorder, _postorder, realid, lastHLD;
	} nodes[maxn];

	int dfs_prep(int i, int p) {
		preorder[i] = pre++;
		sub_size[i] = 1;
		for (int j: adj[i]) {
			if (j == p) continue;
			sub_size[i] += dfs_prep(j,i);
		}
		postorder[i] = pre;
		return sub_size[i];
	}

	void hld(int i, int par, bool newChain) {
        parent[i] = par;
		real_to_hld[i] = hld_id++;
		int id = real_to_hld[i];
		nodes[id]._preorder = preorder[i];
		nodes[id]._postorder = postorder[i];
		nodes[id].realid = i;
		if (newChain) {
			nodes[id].parent = id;
			nodes[id].lastPrev = real_to_hld[par]; //lastprev[1] = 0;
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

int getPfx(int u, int lc, Node *root) {
    int r = 0;
    while (nodes[u].parent != nodes[lc].parent) {
        r ^= root->getsum(nodes[u].parent,u);
        u = nodes[u].lastPrev;
    }
    r ^= root->getsum(lc,u);
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    freopen("cowland.in","r",stdin); freopen("cowland.out","w",stdout);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> val[i];
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_prep(1,0);
    hld(1,0,true);
    Node *root = new Node(0,N);
    for (int i = 1; i <= N; i++) {
        int u = real_to_hld[i];
        root->add(u,val[i]);
    }
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int i, v; cin >> i >> v;
            int u = real_to_hld[i];
            root->add(u,v);
        }
        else {
            int u, v; cin >> u >> v;
            u = real_to_hld[u];
            v = real_to_hld[v];
            int lc = lca(u,v);    
            int res = getPfx(u,lc,root) ^ getPfx(v,lc,root) ^ root->getsum(lc,lc);
            cout << res << '\n';
        }
    }
}

