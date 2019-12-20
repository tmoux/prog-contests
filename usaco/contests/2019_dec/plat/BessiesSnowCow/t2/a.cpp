#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+505;
int n, q;
vector<int> adj[maxn];
const int blk = 500;

int pt = 0;
int tin[maxn], tout[maxn];

void dfs(int i, int p) {
    tin[i] = pt++;
    for (int j: adj[i]) {
        if (j == p) continue;
        dfs(j,i);
    }
    tout[i] = pt-1;
}

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
		if (s != e) {
			l->lazy += lazy;
			l->sum += (l->e - l->s + 1) * lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, ll x) {
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

ll ans[maxn];

set<pair<int,int>> color[maxn]; //disjoint intervals

int main() {
    freopen("snowcow.in","r",stdin); freopen("snowcow.out","w",stdout);
    cin >> n >> q;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    Node *root = new Node(0,n);
    while (q--) {
        int t, x; cin >> t >> x;
        if (t == 1) {
            int c; cin >> c;
            int l = tin[x], r = tout[x];
            auto it = color[c].lower_bound({l,-1});
            auto se = color[c].end();
            auto en = color[c].end();
            if (it != color[c].begin() && prev(it)->second >= l) {
                se = prev(it);
            }
            else if (it != color[c].end() && it->first <= r) {
                se = it;
            }
            if (se != color[c].end()) {
                it = color[c].upper_bound({r,maxn});
                en = it;
                l = min(l,se->first);
                r = max(r,prev(en)->second);
                for (auto it = se; it != en;) {
                    root->add(it->first,it->second,-1);
                    color[c].erase(it++);
                }
            }
            color[c].insert({l,r});
            root->add(l,r,1);
        }
        else if (t == 2) {
            ll ans = root->getsum(tin[x],tout[x]);
            cout << ans << '\n';
        }
    }
}
