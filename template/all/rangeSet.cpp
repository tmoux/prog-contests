#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;
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

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
	Node *root = new Node(1,n);
    
    return 0;
}