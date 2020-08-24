#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, maxk = 18;
int N;
vector<int> adj[maxn];
int P[maxn], T[maxn];
ll A[maxn], B[maxn];
int ans[maxn];

int par[maxk][maxn];
int mn[maxk][maxn];

void dfs(int i, int p) {
    par[0][i] = p;
    mn[0][i] = min(T[i],T[p]);
    for (int k = 1; k < maxk; k++) {
        par[k][i] = par[k-1][par[k-1][i]];
        mn[k][i] = min(mn[k-1][i],mn[k-1][par[k-1][i]]);
    }
    for (int j: adj[i]) if (j != p) {
        dfs(j,i);
    }
}
int getAnc(int i) {
    int cur = i;
    for (int k = maxk-1; k >= 0; k--) {
        if (mn[k][cur] >= T[i]) 
            cur = par[k][cur];
    }
    return cur;
}

vector<pair<int,ll>> events[maxn]; 

struct SegDyn
{
	int s, e, m; //represents range [s,e]
	SegDyn *l, *r;
	ll sum; //sum for this interval
	SegDyn(int _s, int _e) {
		s = _s;
		e = _e;
		m = (s+e)/2;
		l = NULL;
		r = NULL;
		sum = 0;
	}

    SegDyn* copy(int t) { 
        //make a copy of segtree for i <= t
        //all i > t are set to 0
        SegDyn *root = new SegDyn(s,e);        
        if (s == e) {
            assert(s <= t);
            root->sum = sum;
            return root;
        }
        else {
            if (e <= t) {
                root->l = l;
                root->r = r; 
            }
            else if (m + 1 <= t) {
                root->l = l;
                //prepareR();
                if (r) root->r = r->copy(t);
            }
            else {
                //prepareL();
                if (l) root->l = l->copy(t);
            }
            root->pull();
            return root;
        }
    }

	void prepareL() { if (l == NULL) l = new SegDyn(s,m); }
	void prepareR() { if (r == NULL) r = new SegDyn(m+1,e); }

	void pull() {
		sum = 0;
		if (l) sum += l->sum;
		if (r) sum += r->sum;
	}

	void add(int idx, int del) { //a[idx] += del
		if (s == e && s == idx) {
			//at the node, stop
            sum += del;
            return;
		}
		if (idx <= m) {
			prepareL();
			l->add(idx,del);
		}
		else {
			prepareR();
			r->add(idx,del);
		}
		pull(); //updates current node based on the children
	}

	ll getsum(int se, int en) {
		if (se <= s && e <= en) return sum;
		ll res = 0;
		if (l && se <= m) res += l->getsum(se,en);
		if (r && en > m) res += r->getsum(se,en);
		return res;	
	}

    int getDay(ll x) {
        if (s == e) {
            return sum >= x ? s : -1;
        }
        if (l && l->sum >= x) return l->getDay(x);
        else {
            if (l) x -= l->sum;
            if (!r) return -1;
            return r->getDay(x);
        }
    }
};

SegDyn* roots[maxn];

void dfs2(int i, int p) {
    roots[i] = roots[p]->copy(T[i]);
    for (auto pa: events[i]) {
        roots[i]->add(pa.first,pa.second);
    }

    ans[i] = roots[i]->getDay(B[i]);

    for (int j: adj[i]) if (j != p) {
        dfs2(j,i);
    }

    for (auto pa: events[i]) {
        roots[i]->add(pa.first,-pa.second);
    }
}
void solve() {
    cin >> N;
    for (int k = 0; k < maxk; k++) {
        for (int i = 0; i <= N; i++) {
            par[k][i] = 0;
            mn[k][i] = 0;
        }
    }
    for (int i = 0; i <= N; i++) {
        adj[i].clear();
        ans[i] = -1;
        events[i].clear();
    }
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= N; i++) {
        cin >> P[i];
        T[P[i]] = i;
    }
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) cin >> B[i];
    dfs(1,0);
    for (int i = 1; i <= N; i++) {
        int anc = getAnc(i);
        events[anc].push_back({T[i],A[i]});
    }

    roots[0] = new SegDyn(1,N);
    dfs2(1,0);

    //output
    for (int i = 1; i <= N; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

