#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
const int INV = -1;
int N, Q;
vector<int> adj[maxn];

struct Node {
	int s, e, m;
	//covers s,e;
	int sum;
	int lazy;
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
            sum = l->sum + r->sum;
		}
		else {
			l = NULL;
			r = NULL;
            sum = 1;
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

	void add(int st, int en, int x) {
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

    int find(int k) {
        push();
        //cout << s << ' ' << e << '\n';
        if (s == e) return s;
        if (l->sum >= k) {
            return l->find(k);
        }
        return r->find(k-l->sum);
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
};

int minsub[maxn];
int ord[maxn], inv[maxn]; //node to seg, seg to node
int pt = 1;

void prep(int i) {
    minsub[i] = i;
    for (int j: adj[i]) {
        prep(j);
        minsub[i] = min(minsub[i],minsub[j]);
    }
    sort(adj[i].begin(),adj[i].end(),[](int a, int b) {
            return minsub[a] < minsub[b];
            });
}
void dfs(int i) {
    for (int j: adj[i]) {
        dfs(j);
    }
    ord[i] = pt;
    inv[pt] = i;
    pt++;
    //cout << i << ' ';
}

const int maxk = 18;
int par[maxk][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    int rt = -1;
    for (int i = 1; i <= N; i++) {
        int pi; cin >> pi;
        if (pi == 0) rt = i;
        else adj[pi].push_back(i);
        par[0][i] = pi;
    }
    for (int k = 1; k < maxk; k++) {
        for (int i = 1; i <= N; i++) {
            par[k][i] = par[k-1][par[k-1][i]];
        }
    }
    prep(rt);
    dfs(rt);
    Node *root = new Node(1,N);
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int k; cin >> k;
            int r = root->find(k);
            root->add(1,r,0);
            cout << inv[r] << '\n';
        }
        else {
            int v; cin >> v;
            int res = 0;
            for (int k = maxk - 1; k >= 0; k--) {
                if (par[k][v] == 0) continue;
                int nxt = par[k][v];
                if (root->getsum(ord[nxt],ord[nxt]) == 0) {
                    res += (1<<k);
                    v = nxt;
                }
            }
            root->add(ord[v],ord[v],1); //set it to empty
            cout << res << '\n';
        }
    }
}

