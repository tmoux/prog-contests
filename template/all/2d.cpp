#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//2nd dimension will be a dynamic segtree, cuz why not
struct SegDyn
{
	int s, e, m; //represents range [s,e]
	SegDyn *l, *r;
	int sum; //sum for this interval
	SegDyn(int _s, int _e) {
		s = _s;
		e = _e;
		m = (s+e)/2;
		l = NULL;
		r = NULL;
		sum = 0;
	}

	void prepareL() { if (l == NULL) l = new SegDyn(s,m); }
	void prepareR() { if (r == NULL) r = new SegDyn(m+1,e); }

	void pull() {
		sum = 0;
		if (l) sum += l->sum;
		if (r) sum += r->sum;
	}

	void add(int idx, int del) { //a[idx] += del
		//cout << s << ' ' << e << '\n';
		if (s == e && s == idx) {
			//at the node, stop
			sum += del;
			return;
		}
		if (idx <= m) {
			prepareL();
			assert(l);
			l->add(idx,del);
		}
		else {
			prepareR();
			r->add(idx,del);
		}
		pull(); //updates current node based on the children
	}

	int getsum(int se, int en) {
		if (se <= s && e <= en) return sum;
		int res = 0;
		if (l && se <= m) res += l->getsum(se,en);
		if (r && en > m) res += r->getsum(se,en);
		return res;	
	}
};

struct SegNode
{
	int s, e, m; //represents range [s,e]
	SegNode *l, *r;
	SegDyn *root; //root of tree, of x coordinates [s,e]
	SegNode(int _s, int _e, int n) {
		s = _s;
		e = _e;
		m = (s+e)/2;
		if (s == e) {
			//make a new segtree, x = s = e
			root = new SegDyn(0,n);
			l = NULL;
			r = NULL;
			return;
		}
		l = new SegNode(s,m,n); 
		r = new SegNode(m+1,e,n);
		root = new SegDyn(0,n);
	}

};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    


    return 0;
}