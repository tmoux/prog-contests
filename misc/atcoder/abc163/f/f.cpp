#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INV = -1; //invalid number for lazy

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
		lazy = INV;
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
		if (lazy == INV) return;
		if (s != e) {
			l->lazy = lazy;
			l->sum = (l->e - l->s + 1) * lazy;

			r->lazy = lazy;
			r->sum = (r->e - r->s + 1) * lazy;
		}
		lazy = INV;
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

const int maxn = 2e5+5;
int c[maxn], par[maxn];
int n;
vector<int> adj[maxn];

int tin[maxn], tout[maxn], t = 1;
int depth[maxn];

void dfs(int i, int p) {
    par[i] = p;
    depth[i] = depth[p] + 1;
    tin[i] = t++;
    for (int j: adj[i]) if (j != p) {
        dfs(j,i);
    }
    tout[i] = t-1;
}

vector<int> nodes[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        nodes[c[i]].push_back(i);
    }
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    adj[0].push_back(1);
    adj[1].push_back(0);
    dfs(0,0);
    Node *root = new Node(0,n+1);
    root->add(1,n+1,1);
    for (int i = 1; i <= n; i++) {
        nodes[i].push_back(0);
        sort(nodes[i].begin(),nodes[i].end(),[](int a, int b) {
            return depth[a] > depth[b];
                });
        ll ans = 0;
        for (int j: nodes[i]) {
            for (int u: adj[j]) if (u != par[j]) {
                int sz = root->getsum(tin[u],tout[u]);
                ans += 1LL*sz*(sz+1)/2;
                //cout << j << ' ' << u << ": " << sz << endl;
            }
            root->add(tin[j],tout[j],0);
        }

        for (int j: nodes[i]) {
            root->add(tin[j],tout[j],1);
        }

        ans = 1LL*n*(n+1)/2-ans;
        cout << ans << '\n';
    }
}
