#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
#define all(v) v.begin(), v.end()
const int maxn = 100005;
const int INF = 2000000000;
vector<int> tree[4*maxn];
int n, m, arr[maxn];
vector<int> sorted;

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
		return (upper_bound(all(tree[node]),k) - tree[node].begin());
	}
	int mid = (l+r) >> 1;
	int left = node << 1, right = (node<<1)|1;
	return query(left,l,mid,i,j,k) + query(right,mid+1,r,i,j,k);
}

int queryWrap(int i, int j, int k) {
	return query(1,1,n,i,j,k);
}


int processQuery(int i, int j, int k) {
	int low = 1, high = n, mid, ans;
	while (low <= high) {
		int mid = (low+high) >> 1;
		int val = queryWrap(i,j,mid);
		//cout << low << ' ' << high << ' ' << mid << ' ' << val << '\n';
		if (val >= k) {
			ans = mid;
			high = mid-1;
		}
		else {
			low = mid+1;
		}
	}
	return sorted[ans-1];
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		sorted.push_back(arr[i]);
	}
	sort(all(sorted));
	for (int i = 1; i <= n; i++) {
		arr[i] = lower_bound(all(sorted),arr[i]) - sorted.begin() + 1;
	}
	build(1,1,n);
	for (int a = 0; a < m; a++) {
		int i, j, k; cin >> i >> j >> k;
		cout << processQuery(i,j,k) << '\n';
		//cout << queryWrap(i,j,k) << '\n';
	}
	
	
	
	
	return 0;
}