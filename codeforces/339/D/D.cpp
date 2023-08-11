#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

struct Node {
	int s, e, m;
	//coverse s,e;
	int sum;
	bool depth;
	Node *l, *r;

	Node(int a, int b, bool d) {
		s = a;
		e = b;
		depth = d;
		sum = 0;
		if (s != e) {
			m = (s+e)/2;
			l = new Node(s,m,!d);
			r = new Node(m+1,e,!d);
		}
		else {
			l = NULL;
			r = NULL;
		}
	}

	void update(int ind, int x) {
		if (s == e) {
			sum = x;
			return;
		}
		int m = (s+e)/2;
		if (ind <= m) {
			l->update(ind,x);
		}
		else {
			r->update(ind,x);
		}

		if (depth) {
			//xor
			sum = l->sum ^ r->sum;
		}
		else {
			//or
			sum = l->sum | r->sum;
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

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in","r",stdin);
	#endif
	int n, m;
	scanf("%d %d",&n,&m);
	Node* root = new Node(0,(1 << n)-1,n%2==0);
	for (int i = 0; i < (1 << n); i++) {
		int ai; scanf("%d",&ai);
		root->update(i,ai);
		//cout << root->sum << '\n';
	}

	while (m--) {
		int pi, bi; scanf("%d %d",&pi,&bi);
		pi--;
		root->update(pi,bi);
		printf("%d\n",root->sum);
		//cout << root->sum << '\n';
	}
	
	return 0;
}