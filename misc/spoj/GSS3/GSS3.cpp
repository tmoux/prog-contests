#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

struct Node
{
	int bestsum, prefsum, sufsum, total;
};

const int maxn = 50005;
Node tree[4*maxn];
int n, m, arr[maxn];

void mergeNode(Node& node, const Node& left, const Node& right) {
	node.bestsum = max(left.bestsum,max(right.bestsum,left.sufsum+right.prefsum));
	node.prefsum = max(left.prefsum,left.total+right.prefsum);
	node.sufsum = max(right.sufsum,right.total+left.sufsum);
	node.total = left.total + right.total;
}

void build(int node, int l, int r) {
	if (l == r) {
		tree[node] = {arr[l],arr[l],arr[l],arr[l]};
		return;
	}
	int mid = (l+r) >> 1;
	int left = node << 1, right = (node<<1)|1;
	
	build(left,l,mid);
	build(right,mid+1,r);
	mergeNode(tree[node],tree[left],tree[right]);
}

void query(Node& res, int node, int l, int r, int i, int j) {
	if (l == i && r == j) {
		res = tree[node];
	}
	else {
		int mid = (l+r) >> 1;
		int left = node << 1, right = (node<<1)|1;
		if (j <= mid) {
			query(res,left,l,mid,i,j);
		}
		else if (i > mid) {
			query(res,right,mid+1,r,i,j);
		}
		else {
			Node leftNode, rightNode;
			query(leftNode,left,l,mid,i,mid);
			query(rightNode,right,mid+1,r,mid+1,j);
			mergeNode(res,leftNode,rightNode);
		}
	}
	
}

void update(int node, int l, int r, int idx, int val) {
	if (l > r || l > idx || r < idx) return;
	if (l == r) {
		tree[node] = {val,val,val,val};
		return;
	}
	int mid = (l+r) >> 1;
	int left = node << 1, right = left|1;
	update(left,l,mid,idx,val);
	update(right,mid+1,r,idx,val);
	mergeNode(tree[node],tree[left],tree[right]);
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
	cin >> m;
	while (m--) {
		int id, x, y;
		cin >> id >> x >> y;
		switch (id) {
			case 0:
				update(1,1,n,x,y);
				break;
			case 1:
				Node res;
				query(res,1,1,n,x,y);
				cout << res.bestsum << '\n';
				break;
		}
	}
	
	return 0;
}