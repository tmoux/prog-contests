#include <bits/stdc++.h>
using namespace std;

struct Node {/*{{{*/
	int s, e, m;
	//covers s,e;
	int sum;
	int lazy;
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
		if (s != e) {
			l->lazy += lazy;
			l->sum += (l->e - l->s + 1) * lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, int x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
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
	}

	int getsum(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return sum;
		}
		int ret = 0;
		if (st <= m) {
			ret += l->getsum(st,en);
		}
		if (en > m) {
			ret += r->getsum(st,en);
		}
		return ret;
	}
};/*}}}*/

const int maxn = 1e5+5;
int n, m;
vector<int> adj[maxn];

int tin[maxn], tout[maxn];
int subsize[maxn];
int dfs(int i, int p, int& t) {
  tin[i] = t++;
  subsize[i] = 1;
  for (int j: adj[i]) if (j != p) 
    subsize[i] += dfs(j, i, t);
  tout[i] = t-1;
  return subsize[i];
}

vector<int> v[maxn];
vector<int> color[maxn];

int ans[maxn];
Node *root;
vector<pair<int, array<int,3>>> st;
void dfs2(int i, int p) {
  for (int c: v[i]) {
    for (int x: color[c]) {
      if (root->getsum(tin[x], tin[x]) == 0) {
        int sum = root->getsum(tin[x], tout[x]);
        assert(sum <= subsize[x]);
        root->add(tin[x], tout[x], 1);
        st.push_back({i, {tin[x], tout[x], 1}});
        root->add(tin[x], tin[x], -sum);
        st.push_back({i, {tin[x], tin[x], -sum}});

      }
    }
  }
  ans[i] = max(0, root->getsum(0, n-1)-1);
  for (int j: adj[i]) if (j != p) dfs2(j, i);
  while (!st.empty() && st.back().first == i) {
    auto [l, r, x] = st.back().second;
    st.pop_back();
    root->add(l, r, -x);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < n-1; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int t = 0;
  dfs(1, 1, t);

  for (int i = 1; i <= m; i++) {
    int a, b; cin >> a >> b;
    color[i] = {a, b};
    v[a].push_back(i);
    v[b].push_back(i);
  }
  root = new Node(0, n);
  dfs2(1, 1);
  
  for (int i = 1; i <= n; i++) {
    cout << ans[i] << " \n"[i==n];
  }
}
