#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 4e5+5;
int A[maxn];

struct Node {/*{{{*/
	int s, e, m;
	//covers s,e;
	ll sum;
  int lazy;
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
		if (s != e && lazy != -1) {
			l->lazy = lazy;
			l->sum = 1LL<<lazy;

			r->lazy = lazy;
      r->sum = 1LL<<lazy;
		}
    lazy = -1;
	}

	void add(int st, int en, int x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy = x;
			sum = 1LL<<x;
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		sum = l->sum | r->sum;
	}

	ll getsum(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return sum;
		}
		ll ret = 0;
		if (st <= m) {
			ret |= l->getsum(st,en);
		}
		if (en > m) {
			ret |= r->getsum(st,en);
		}
		return ret;
	}
};/*}}}*/

int n, m;
vector<int> adj[maxn];
int tin[maxn], tout[maxn], t = 1;

void dfs(int i, int p) {
  tin[i] = t++;
  for (int j: adj[i]) if (j != p) {
    dfs(j, i);
  }
  tout[i] = t-1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m;
  Node *root = new Node(1, n);
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
  }
  for (int i = 0; i < n-1; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dfs(1, 1);
  for (int i = 1; i <= n; i++) {
    root->add(tin[i], tin[i], A[i]);
  }
  for (int qq = 0; qq < m; qq++) {
    int t; cin >> t;
    if (t == 1) {
      int v, c; cin >> v >> c;
      root->add(tin[v], tout[v], c);
    }
    else {
      int v; cin >> v;
      int ans = __builtin_popcountll(root->getsum(tin[v], tout[v]));
      cout << ans << '\n';
    }
  }
}
