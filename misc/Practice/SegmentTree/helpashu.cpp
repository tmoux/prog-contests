#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 1000001;

int arr[maxn];
int N;
pair<int,int> tree[4*maxn];
int lazy[4*maxn];

struct SegTree 
{
	void build(int n=1, int left=0, int right=N) {
		if (left > right) return;
		else if (left == right) {
			tree[n] = make_pair(arr[left] % 2 == 0, arr[left] % 2 == 1);
			return;
		}
		int mid = (left+right)/2;
		build(n*2,left,mid);
		build(n*2+1,mid+1,right);
		//the tree stores the sum of the child nodes,
		//but can be max or any operation I guess
		tree[n].first = tree[n*2].first + tree[n*2+1].first;
		tree[n].second = tree[n*2].second + tree[n*2+1].second;
	}

	void update(int index, int val, int n=1, int left=0, int right = N) {
		if (left == right) {
			//this means we are at the leaf node
			tree[n] = make_pair(val % 2 == 0, val % 2 == 1);
			return;
		}
		else {
			int mid = (left+right)/2;
			if (left <= index && index <= mid) {
				update(index,val,2*n,left,mid);
			}
			else {
				update(index,val,2*n+1,mid+1,right);
			}
			tree[n].first = tree[n*2].first + tree[n*2+1].first;
			tree[n].second = tree[n*2].second + tree[n*2+1].second;
		}
		//rechange the current node
		
	}

	int query1(int i, int j, int n=1, int left=0, int right=N) {
		//queries for [i,j] (INCLUSIVE)
		//queries for the sum
		if (left > right || j < left || right < i) {
			return 0;
		}
		if (i <= left && right <= j) {
			//cout << left << ' ' << right << ' ' << n << '\n';
		
			return tree[n].first;
		}
		int mid = (left+right)/2;
		int p1 = query1(i,j,2*n,left,mid);
		int p2 = query1(i,j,2*n+1,mid+1,right);
		return p1+p2;	
	}

	int query2(int i, int j, int n=1, int left=0, int right=N) {
		//queries for [i,j] (INCLUSIVE)
		//queries for the sum
		if (left > right || j < left || right < i) {
			return 0;
		}
		if (i <= left && right <= j) {
			//cout << left << ' ' << right << ' ' << n << '\n';
		
			return tree[n].second;
		}
		int mid = (left+right)/2;
		int p1 = query2(i,j,2*n,left,mid);
		int p2 = query2(i,j,2*n+1,mid+1,right);
		return p1+p2;	
	}
};


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("helpashu.in","r",stdin);
	SegTree segtree;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	
	segtree.build();
	int Q; cin >> Q;
	for (int i = 0; i < Q; i++) {
		int mode, x, y;
		cin >> mode >> x >> y;
		switch (mode) {
			case 0:
				segtree.update(x-1,y);
				break;
			case 1:
				cout << segtree.query1(x-1,y-1) << '\n';
				break;
			case 2:
				cout << segtree.query2(x-1,y-1) << '\n';
				break;
		}
	}
	
	return 0;
}

