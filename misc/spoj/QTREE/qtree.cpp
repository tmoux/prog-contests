#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10005;
int n, preorder[maxn], postorder[maxn], sub_size[maxn], weight[maxn], real_to_hld[maxn];
int pre = 0, hld_id = 1;
vector<int> adj[maxn];
map<pair<int,int>,pair<int,int>> mp;
struct Node {
	int parent, lastPrev, _preorder, _postorder;
} nodes[maxn];

class Seg {
public:
	int s, e, m;
	//covers s,e;
	int maxi = 0;
	Seg *l, *r;

	Seg(int a, int b) {
		s = a;
		e = b;
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

	void add(int ind, int x) {
		if (s == e) {
			maxi = x;
			return;
		}
		int m = (s+e)/2;
		if (ind <= m) {
			l->add(ind,x);
		}
		else {
			r->add(ind,x);
		}
		maxi = max(l->maxi,r->maxi);
	}

	int getmaxi(int st, int en) {
		if (en < st) return 0;
		//if completely included
		if (st <= s && e <= en) {
			return maxi;
		}
		int ret = 0;
		if (st <= m) {
			ret = max(ret,l->getmaxi(st,en));
		}
		if (en > m) {
			ret = max(ret,r->getmaxi(st,en));
		}
		return ret;
	}

	void cleanup() {
		if (l) l->cleanup();
		if (r) r->cleanup();
		delete this;
	}
};

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

void hld(int i, int par, bool newChain, Seg* root) {
	real_to_hld[i] = hld_id++;
	
	int id = real_to_hld[i];
	nodes[id]._preorder = preorder[i];
	nodes[id]._postorder = postorder[i];
	root->add(id,weight[i]);
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
		if (sub_size[j] * 2 >= sub_size[i]) hld(j,i,false,root);
	}
	for (int j: adj[i]) {
		if (j == par) continue;
		if (sub_size[j] * 2 < sub_size[i]) hld(j,i,true,root);
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

int query(int u, int lc, Seg* root) {
	int res = 0;
	while (nodes[u].parent != nodes[lc].parent) {
		res = max(res,root->getmaxi(nodes[u].parent,u));
		u = nodes[u].lastPrev;
	}
	res = max(res,root->getmaxi(lc+1,u));
	return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    #ifdef OFFLINE
    freopen("in","r",stdin);
    #endif
    int t; cin >> t;
    while (t--) {
    	cin >> n;
    	//clear everything
    	//memset(preorder,0,sizeof(preorder));
    	//memset(postorder,0,sizeof(postorder));
    	//memset(sub_size,0,sizeof(sub_size));
    	//memset(weight,0,sizeof(weight));
    	//memset(weight,0,sizeof(weight));
    	//memset(edge_to_real,0,sizeof(edge_to_real));
        pre = 0, hld_id = 1;
    	//for (int i = 1; i <= n; i++) nodes[i] = {0,0,0,0};
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
    	Seg* root = new Seg(0,n);
    	hld(1,1,true,root);

    	while (true) {
    		string s; cin >> s;
    		if (s == "DONE") break;
    		if (s == "CHANGE") {
    			int i, ti; cin >> i >> ti;
    			int id = real_to_hld[edge_to_real[i]];
    			root->add(id,ti);
    		}
    		else {
    			int a, b; cin >> a >> b;
    			int u = real_to_hld[a], v = real_to_hld[b];
    			int lc = lca(u,v);
    			int res = query(u,lc,root);
    			res = max(res,query(v,lc,root));
    			cout << res << '\n';
    		}
    	}
    	root->cleanup();
    }

    return 0;
}
