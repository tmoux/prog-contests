#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+5;

template<typename T>
void amax(T& a, T b) {
	a = max(a,b);
}

struct SegDyn
{
	int s, e, m; //represents range [s,e]
	SegDyn *l, *r;
	int mx; //sum for this interval
	SegDyn(int _s, int _e) {
		s = _s;
		e = _e;
		m = (s+e)/2;
		l = NULL;
		r = NULL;
		mx = 0;
	}

	void prepareL() { if (l == NULL) l = new SegDyn(s,m); }
	void prepareR() { if (r == NULL) r = new SegDyn(m+1,e); }

	void pull() {
		mx = 0;
		if (l) amax(mx,l->mx);
		if (r) amax(mx,r->mx);
	}

	void update(int idx, int del) { //a[idx] = max(a[idx,del)
		//cout << s << ' ' << e << '\n';
		if (s == e && s == idx) {
			//at the node, stop
			mx = max(mx,del);
			return;
		}
		if (idx <= m) {
			prepareL();
			l->update(idx,del);
		}
		else {
			prepareR();
			r->update(idx,del);
		}
		pull(); //updates current node based on the children
	}

	int getmax(int se, int en) {
		if (se > en) return 0;
		if (se <= s && e <= en) return mx;
		int res = 0;
		if (l && se <= m) amax(res,l->getmax(se,en));
		if (r && en > m) amax(res,r->getmax(se,en));
		return res;	
	}
};

SegDyn* segs[maxn];

int main()
{
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		segs[i] = new SegDyn(0,maxn);
	}
	int ans = 0;
	while (m--) {
		int a, b, w; cin >> a >> b >> w;
		//split into two directed edges, a->b, b->a
		int m1 = segs[a]->getmax(0,w-1) + 1;
		segs[b]->update(w,m1);
		amax(ans,m1);
	}
	cout << ans << '\n';
}