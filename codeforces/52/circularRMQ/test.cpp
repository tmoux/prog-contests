#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>
using namespace std;
typedef long long ll;
//change ints to ll's if actually trying to submit this

const int maxn = 20005;
const int INF = 2000000000;
int arr[maxn];
int N, M;

struct SegTree
{
int sz;
int hi[4*maxn+1], lo[4*maxn+1];
ll tree[4*maxn+1], delta[4*maxn+1];

SegTree(int ni) {
	sz = ni;
	build(1,1,sz);
}
//void build
//for (int i = 0; i < N; i++)[
void build(int node, int l, int r) {
	lo[node] = l;
	hi[node] = r;
	if (l == r) {
		tree[node] = arr[l];
		return;
	}
	int mid = (l+r)>>1;
	build(2*node,l,mid);
	build(2*node+1,mid+1,r);
	updateNode(node);
}
void prop(int i) {
	delta[2*i] += delta[i];
	delta[2*i+1] += delta[i];
	delta[i] = 0;
}
void updateNode(int i) {
	tree[i] = min(tree[2*i]+delta[2*i],tree[2*i+1]+delta[2*i+1]);
}
void update(int l, int r, int val) {
	update(1,l,r,val);
}
void update(int n, int l, int r, int val) {
	if (r < lo[n] || hi[n] < l) {
		return;
	}
	if (l <= lo[n] && hi[n] <= r) {
		delta[n] += val;
		return;
	}
	//Partial coverage on [lo[n],hi[n]]
	prop(n);
	update(2*n,l,r,val);
	update(2*n+1,l,r,val);
	updateNode(n);
}
int query(int n, int l, int r) {
	if (r < lo[n] || hi[n] < l) {
		return INF;
	}
	if (l <= lo[n] && hi[n] <= r) {
		return tree[n]+delta[n];
	}
	prop(n);
	updateNode(n);
	return min(query(2*n,l,r),query(2*n+1,l,r));
}

};
//this is insert mode
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.in","r",stdin);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
	}
	SegTree segtree(N);
	cin >> M;
	string s;
	getline(cin,s);
	while (M--) {
		int lf, rg, v = -INF;
		getline(cin,s);
		stringstream stream(s);
		stream >> lf >> rg;
		lf++;
		rg++;
		if (stream >> v) {
			//update
			if (lf <= rg) {
				segtree.update(lf,rg,v);
			}
			else {
				segtree.update(lf,N,v);
				segtree.update(1,rg,v);
			}
		}
		else {
			//query
			//cout << lf << ' ' << rg << '\n';
			if (lf <= rg) {
				cout << segtree.query(1,lf,rg) << '\n';
			}
			else {
				cout << min(segtree.query(1,lf,N),segtree.query(1,1,rg)) << '\n';
			}
		}
		
	}
	
	return 0;
}
