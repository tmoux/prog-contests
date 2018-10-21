#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100005;
const ll NEG = -1e18;
int n, q, preorder[maxn], postorder[maxn], sub_size[maxn], weight[maxn], real_to_hld[maxn];
int pre = 0, hld_id = 1;
vector<int> adj[maxn];
struct Node {
	int parent, lastPrev, _preorder, _postorder, realid, sub;
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
	nodes[id].sub = hld_id-1;
	//cout << i << ' ' << nodes[hld_id-1].realid << '\n';
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

struct Seg {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll lazy;
	ll maxi;
	Seg *l, *r;
	
	Seg(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
		maxi = 0;
		if (s != e) {
			m = (s+e)/2;
			l = new Seg(s,m);
			r = new Seg(m+1,e);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}

	void push() {
		if (s != e) {
			l->lazy += lazy;
			l->sum += (l->e - l->s + 1) * lazy;
			l->maxi += lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
			r->maxi += lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, ll x) {
		if (st > en) return;
		//lazy: already accounted for in your own node, not the childs nodes
		//push();
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
			maxi += x;
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		sum = l->sum + r->sum;
		maxi = max(l->maxi,r->maxi);
	}

	ll getmaxi(int st, int en) {
		if (st > en) return NEG;
		push();
		//if completely included
		if (st <= s && e <= en) {
			return maxi;
		}
		ll ret = NEG;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}	
};

ll query(int u, int lc, Seg* seg) {
	ll res = NEG;
	while (nodes[u].parent != nodes[lc].parent) {
		res = max(res,seg->getmaxi(nodes[u].parent,u));
		u = nodes[u].lastPrev;
	}
	res = max(res,seg->getmaxi(lc,u));
	return res;
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 1; i <= n - 1; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs_prep(1,1);
	hld(1,1,true);

	Seg* seg = new Seg(1,n);
	cin >> q;
	while (q--) {
		char c; cin >> c;
		if (c == 'I') {
			int t, val; cin >> t >> val;
			int u = real_to_hld[t];
			seg->add(u,u,val);
			/*
			cout << u << ' ' << nodes[u].sub << ' ' << val << ":\n";
			for (int i = 1; i <= n; i++) {
				cout << i << ": " << seg->getmaxi(i,i) << '\n';
			}
			*/
		}		
		else {
			int a, b; cin >> a >> b;
			int u = real_to_hld[a], v = real_to_hld[b];
			int lc = lca(u,v);
			ll res = max(query(u,lc,seg),query(v,lc,seg));
			cout << res << '\n';
		}
	}	

    return 0;
}