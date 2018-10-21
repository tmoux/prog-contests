#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int numBits(int a) {
	int res = 0;
	while (a) {
		if (a&1) res++;
		a >>= 1;
	}
	return res;
}

class Node {
public:
	int s, e, m;
	//coverse s,e;
	int sum;
	int maxi;
	int maxk;
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
		if (s == e) {
			sum = x;
			maxi = numBits(sum);
			maxk = sum;
			return;
		}
		int m = (s+e)/2;
		if (ind <= m) {
			l->add(ind,x);
		}
		else {
			r->add(ind,x);
		}

		if (l->maxi > r->maxi) {
			maxi = l->maxi;
			maxk = l->maxk;
		}
		else if (r->maxi > l->maxi) {
			maxi = r->maxi;
			maxk = r->maxk;
		}
		else {
			maxi = l->maxi;
			maxk = max(l->maxk,r->maxk);
		}
		sum = l->sum + r->sum;
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

	pair<int,int> getmaxk(int st, int en) {
		//if completely included
		if (st <= s && e <= en) {
			return {maxi,maxk};
		}
		pair<int,int> ret = {0,0};
		if (st <= m) {
			pair<int,int> l1 = l->getmaxk(st,en);
			if (l1.first > ret.first) {
				ret = l1;
			}
			else if (l1.first == ret.first) {
				ret.second = max(ret.second,l1.second);
			}
		}
		if (en > m) {
			pair<int,int> r1 = r->getmaxk(st,en);
			if (r1.first > ret.first) {
				ret = r1;
			}
			else if (r1.first == ret.first) {
				ret.second = max(ret.second,r1.second);
			}
		}
		return ret;
	}
};

const int maxn = 100005;
int n, q;
vector<int> child[maxn];
int preorder[maxn], skip[maxn];
int A[maxn];
int pre = 0;

void dfs(int i) {
	preorder[i] = pre++;
	for (int c: child[i]) {
		dfs(c);
	}
	skip[i] = pre-1;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> q;
	Node *root = new Node(0,n-1);
	for (int i = 0; i < n; i++) {
		int ai; cin >> ai;
		A[i] = ai;
		//root->add(i,ai);
	}		
	for (int i = 1; i <= n - 1; i++) {
		int ai; cin >> ai;
		ai--;
		child[ai].push_back(i);
	}

	dfs(0);
	for (int i = 0; i < n; i++) {
		root->add(preorder[i],A[i]);
        cout << i << ": " << preorder[i] << ' ' << skip[i]<< '\n';
	}

	while (q--) {
		int t; cin >> t;
		if (t == 1) {
			int r; cin >> r;
			r--;
			cout << root->getmaxk(preorder[r],preorder[skip[r]]).second << '\n';
			//cout << preorder[r] << ' ' << skip[r] << '\n';

		}
		else {
			int r, c; cin >> r >> c;
			r--;
			//cout << preorder[r] << ' ' << skip[r] << '\n';
			root->add(preorder[r],c);
		}
	}

	return 0;
}
