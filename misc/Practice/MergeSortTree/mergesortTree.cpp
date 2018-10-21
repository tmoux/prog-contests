#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
#define all(v) v.begin(), v.end()
const int maxn = 100005;
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
		return lower_bound(all(tree[node]),k) - tree[node].begin();
	}
	int mid = (l+r) >> 1;
	int left = node << 1, right = (node<<1)|1;
	return query(left,l,mid,i,j,k) + query(right,mid+1,r,i,j,k);
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int ai; cin >> ai;
		
	}
	
	
	return 0;
}