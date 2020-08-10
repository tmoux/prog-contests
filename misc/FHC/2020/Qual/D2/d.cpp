#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
const ll INF = 1e18;

struct Node {
	int s, e, m;
	//covers s,e;
	ll sum;
	ll mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = INF;
		mini = INF;
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

	void add(int i, ll x) {
		if (s == e) {
			sum = min(sum,x);
			mini = sum;
			return;
		}
		if (i <= m) {
			l->add(i,x);
		}
		else if (i > m) {
			r->add(i,x);
		}
		else assert(false);
		sum = l->sum + r->sum;
		mini = min(l->mini,r->mini);
	}

	ll getmini(int st, int en) {
		if (st <= s && e <= en) {
			return mini;
		}
		ll ret = INF;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}	

	ll getsum(int st, int en) {
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
ll c[maxn];
int depth[maxn];
int par[maxn];
int n, m, A, B;
void dfs(int i, int p) {
    par[i] = p;
    depth[i] = depth[p] + 1;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
}
void dfs2(int i, int p, int orig_depth, Node *root) {
    if (m-(depth[i]-orig_depth) > 0) {
        ll cost = root->getmini(depth[i],n)+c[i];
        root->add(min(n,orig_depth+m-(depth[i]-orig_depth)),cost);
        for (int j: adj[i]) if (j != p) {
            dfs2(j,i,orig_depth,root);
        }
    }
}
void solve() {
    cin >> n >> m >> A >> B;
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        c[i] = 0;
        depth[i] = 0;
        par[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        int pi;
        cin >> pi >> c[i];
        if (pi) {
            adj[pi].push_back(i);
            adj[i].push_back(pi);
        }
        if (c[i] == 0) c[i] = INF;
    }
    dfs(A,A);
    vector<int> v = {B};
    while (v.back() != A) {
        v.push_back(par[v.back()]);
    }
    reverse(v.begin(),v.end());
    Node *root = new Node(1,n);
    root->add(min(n,m+1),0);
    for (int i = 1; i < (int)(v.size())-1; i++) {
        int u = v[i];
        int nxt = v[i+1];
        int p = v[i-1];
        ll cost = root->getmini(depth[u],n)+c[u];
        root->add(min(n,depth[u]+m),cost);
        for (int j: adj[u]) {
            if (j == nxt || j == p) continue;
            dfs2(j,u,depth[u],root);
        }
    }
    ll ans = root->getmini(depth[B],n);
    cout << (ans == INF ? -1 : ans) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int iter = 1; iter <= t; iter++) {
        cout << "Case #" << iter << ": ";
        solve();
    }
}
