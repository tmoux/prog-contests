#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
#define all(v) v.begin(), v.end()
const int maxn = 30005;
vector<int> tree[4*maxn];
int n, m, arr[maxn];

void build(int node, int l, int r) {
	if (l == r) {
		tree[node].push_back(arr[l]);
		return;
	}
	int mid = (l+r) >> 1;
	int left = node << 1, right = (node<<1)|1;
	
	build(left,l,mid);
	build(right,mid+1,r);
	merge(all(tree[left]),all(tree[right]),back_inserter(tree[node]));
}

int query(int node, int l, int r, int i, int j, int k) {
	if (i > r || j < l) return 0;
	if (i <= l && r <= j) {
		return (r-l+1) - (upper_bound(all(tree[node]),k) - tree[node].begin());
	}
	int mid = (l+r) >> 1;
	int left = node << 1, right = (node<<1)|1;
	return query(left,l,mid,i,j,k) + query(right,mid+1,r,i,j,k);
}

int processQuery(int i, int j, int k) {
	if (i < 1) i = 1;
	if (j > n) j = n;
	if (i > j) return 0;
	return query(1,1,n,i,j,k);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	build(1,1,n);
	int q; cin >> q;
	int last_ans = 0;
	for (int a = 0; a < q; a++) {
		int i, j, k; cin >> i >> j >> k;
		i ^= last_ans;
		j ^= last_ans;
		k ^= last_ans;
		last_ans = processQuery(i,j,k);
		cout << last_ans << '\n';
	}
	
	
	
	
	
	return 0;
}