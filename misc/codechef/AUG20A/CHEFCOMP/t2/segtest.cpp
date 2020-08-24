#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
            //cout << "s = " << s << ", t = " << t << endl;
            //assert(s <= t);
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
                prepareR();
                root->r = r->copy(t);
            }
            else {
                prepareL();
                root->l = l->copy(t);
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

	SegDyn* add(int idx, int del) { //a[idx] += del
		if (s == e && s == idx) {
			//at the node, stop
            SegDyn* root = new SegDyn(s,e);
			root->sum += del;
			return root;
		}
        SegDyn* root = new SegDyn(s,e);
		if (idx <= m) {
			prepareL();
			root->l = l->add(idx,del);
            root->r = r;
		}
		else {
			prepareR();
			root->r = r->add(idx,del);
            root->l = l;
		}
		root->pull(); //updates current node based on the children
        return root;
	}

	ll getsum(int se, int en) {
		if (se <= s && e <= en) return sum;
		ll res = 0;
		if (l && se <= m) res += l->getsum(se,en);
		if (r && en > m) res += r->getsum(se,en);
		return res;	
	}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    SegDyn *root1 = new SegDyn(1,10);
    SegDyn *root2 = root1->add(2,3);
    SegDyn *root3 = root2->add(7,9);
    cout << root3->getsum(2,9) << '\n';
    cout << root2->getsum(1,10) << '\n';
    cout << root1->getsum(1,10) << '\n';

    SegDyn *root4 = root3->add(5,4);
    SegDyn *root5 = root4->copy(1);
    SegDyn *root6 = root5->add(5,99);
    cout << root6->getsum(1,10) << '\n';
}
