#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

class Node {
public:
	int s, e, m;
	//coverse s,e;
	int sum;
	int lazy;
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
			r->sum += (l->e - l->s + 1) * lazy;

		}
		lazy = 0;
	}

	void pull() {
		sum = l->sum + r->sum;
	}

	void add(int st, int en, int x) {
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
		//write in "pull" function
		pull();
	}

	int kth(int k) {
		if (s==e) {
			return s;
		}
		push();
		if (l->sum >= k) {
			//walk to the left
			return l->kth(k);
		}
		k -= l->sum;
		return r->kth(k);
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

int main() {
	int ar[6] = {7,7,7,7,7,7};
	Node *root = new Node(0,5);
	for (int i = 0; i < 6; i++) {
		root->add(i,i,ar[i]);
	}
	cout << root->getsum(0,5) << '\n';
	root->add(0,5,4);
	cout << root->getsum(0,1) << '\n';
	cout << root->kth(12) << '\n';

}