#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//dynamic segment tree for sum. Careful that it uses int to store sum.
//updates (adding) will cost at most O(log n) memory
//queries will cost no additional memory, as it never creates new nodes
//Both are O(log n) time

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

int n, q;

int getSmallest(int i, SegDyn *root) {
	int lo = 0, hi = n;
	while (lo + 1 < hi) {
        int m = (lo+hi)/2;
        int j = m - root->getsum(0,m);
        if (j >= i) hi = m;
        else lo = m;
    }
    return lo + 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    SegDyn *root = new SegDyn(0,n);
    while (q--) {
        char c; cin >> c; 
        int i; cin >> i;
        if (c == 'L') {
            cout << getSmallest(i,root) << '\n'; 
        }
        else {
            root->add(getSmallest(i,root),1);
        }
    }

    return 0;
}
