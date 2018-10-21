#include <iostream>
using namespace std;

class Node {
public:
	int s, e, m;
	//covers s,e;
	int sum;
	Node *l, *r;

	Node(int a, int b) {
		s = a;
		e = b;
		sum = 0;
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

	int getsum(int st, int en) {
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
	int ar[8] = {3,6,9,2,4,5,1,3};
	Node *root = new Node(0,7);
	for (int i = 0; i < 8; i++) {
		root->add(i,ar[i]);
	}
	cout << root->getsum(0,5) << '\n';
}