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
	int mini;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
		lazy = 0;
		mini = 0;
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

	void add(int ind, int x) {
		sum += x;
		if (s == e) {
			return;
		}
		int m = (s+e)/2;
		if (ind <= m) {
			l->add(ind,x);
		}
		else {
			r->add(ind,x);
		}
	}

	void push() {
		if (s != e) {
			l->lazy += lazy;
			l->sum += (l->e - l->s + 1) * lazy;
			l->mini += lazy;

			r->lazy += lazy;
			r->sum += (r->e - r->s + 1) * lazy;
			r->mini += lazy;
		}
		lazy = 0;
	}

	void add(int st, int en, int x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy += x;
			sum += (e - s + 1) * x;
			mini += lazy;
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
		mini = min(l->mini,r->mini);
	}

	int getmini(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return mini;
		}
		int ret = 999999999;
		if (st <= m) {
			ret = l->getmini(st,en);
		}
		if (en > m) {
			ret = r->getmini(st,en);
		}
		return ret;
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
	cout << root->getmini(0,5) << '\n';
	root->add(0,5,4);
	cout << root->getmini(0,1) << '\n';

}