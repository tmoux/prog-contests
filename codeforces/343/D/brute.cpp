#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5+5;
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
		lazy = 0;
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
		if (lazy == 0) return;
		if (s != e) {
			l->lazy = lazy;
			l->sum = (l->e - l->s + 1) * lazy;

			r->lazy = lazy;
			r->sum = (r->e - r->s + 1) * lazy;
		}
		lazy = 0;
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

vector<int> adj[maxn];
int preorder[maxn], postorder[maxn];
int par[maxn];
int pre = 0;

void dfs(int i, int p) {
	par[i] = p;
	preorder[i] = ++pre;
	for (int j: adj[i]) {
		if (j == p) continue;
		dfs(j,i);
	}
	postorder[i] = pre;
}

int main()
{
	//freopen("in","r",stdin);
    ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1,1);
	Node *seg = new Node(1,n);
	cin >> q;
	while (q--) {
		int t, v; cin >> t >> v;
		if (t == 1) {
			//fill children
			seg->add(preorder[v],postorder[v],1);
		}
		else if (t == 2) {
			while (true) {
				seg->add(preorder[v],preorder[v],0);
				if (v == par[v]) break;
				v = par[v];
			}
		}
		else {
			int ans = seg->getsum(preorder[v],preorder[v]);
			cout << ans << '\n';
		}
		/*
		for (int i = 1; i <= n; i++) {
			cout << seg->getsum(preorder[i],preorder[i]) << ' ';
		}
		cout << '\n';
		*/
	}	
	
	
	
	
	
	
	
    return 0;
}