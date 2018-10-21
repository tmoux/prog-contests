#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
#define all(v) v.begin(), v.end()
const int maxn = 200005;
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

ll query(int node, int l, int r, int i, int j, int k) {
	if (i > r || j < l) return 0;
	if (i <= l && r <= j) {
		return (r-l+1) - (lower_bound(all(tree[node]),k) - tree[node].begin());
		//(total # elements) - (# strictly smaller than k) = # greater than or equal to k
	}
	int mid = (l+r) >> 1;
	int left = node << 1, right = (node<<1)|1;
	return query(left,l,mid,i,j,k) + query(right,mid+1,r,i,j,k);
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	build(1,1,n);
	
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += query(1,1,n,1,min(n,arr[i]),i);
		if (arr[i] >= i) ans--;
	}
	ans /= 2;
	cout << ans << '\n';	
	return 0;
}