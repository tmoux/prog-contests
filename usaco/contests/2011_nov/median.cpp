/*
ID: silxikys
PROG: median
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;
ofstream fout("median.out");
ifstream fin("median/I.10");

class Node {
public:
	int s, e, m;
	//covers s,e;
	int sum;
	int mini = 0;
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
			mini = sum;
			return;
		}
		int m = (s+e)/2;
		if (ind <= m) {
			l->add(ind,x);
		}
		else {
			r->add(ind,x);
		}
		mini = min(l->mini,r->mini);
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

	int getmini(int st, int en) {
		//if completely included
		if (st <= s && e <= en) {
			return mini;
		}
		int ret = 999999999;
		if (st <= m) {
			ret = min(ret,l->getmini(st,en));
		}
		if (en > m) {
			ret = min(ret,r->getmini(st,en));
		}
		return ret;
	}

	int getR(int k) {

	}
};

const int maxn = 1e5+5;
int N, X, pre[maxn];

int main() 
{
	fin >> N >> X;
	Node* root = new Node(0,2*N);
	for (int i = 1; i <= N; i++) {
		fin >> pre[i];
		pre[i] = (pre[i] >= X ? 1 : -1);
		pre[i] += pre[i-1];
		root->add(pre[i]+N,1);
	}

	ll ans = 0LL;
	for (int i = 1; i <= N; i++) {
		ans += root->getsum(pre[i-1]+N,2*N);
		root->add(pre[i]+N,-1);
        //cout << i << ' ' << ans << '\n';
	}

    cout << ans << '\n';
    fout << ans << '\n';
	return 0;
}
