#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 100001;
int tree[4*maxn];
int n, q, arr[maxn];

void build(int node, int l, int r) {
	if (l == r) {
		tree[node] = arr[l];
		return;
	}
	int mid = (l+r) >> 1;
	int left = node << 1, right = (node<<1)|1;
	
	build(left,l,mid);
	build(right,mid+1,r);
	tree[node] = max(0,tree[left]) + max(0,tree[right]);
	cout << l << ' ' << r << ' ' << tree[node] << '\n';
}

int query(int node, int l, int r, int i, int j) {
	if (l > r || j < l || i > r) {
		return 0;
	}
	if (i <= l && r <= j) {
		return tree[node];
	}
	int mid = (l+r) >> 1;
	int left = node << 1, right = left|1;
	return query(left,l,mid,i,j) + query(right,mid+1,r,i,j);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.in","r",stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	build(1,1,n);
	cin >> q;
	int x, y;
	while (q--) {
		cin >> x >> y;
		cout << query(1,1,n,x,y) << '\n';
	}
	
	
	return 0;
}