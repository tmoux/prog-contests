#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 2000001;
const int INF = 999999999;
int tree[4*maxn];
int lazy[4*maxn];
int arr[maxn];
int N;

void build(int n, int left, int right) {
	if (left > right) return;
	else if (left == right) {
		tree[n] = arr[left];
		return;
	}
	int mid = (left+right)/2;
	build(n*2,left,mid);
	build(n*2+1,mid+1,right);
	//the tree stores the sum of the child nodes,
	//but can be max or any operation I guess
	tree[n] = min(tree[n*2],tree[n*2+1]);
}

void printArray() {
	int size = 1;
	for (; size < N; size <<= 1) {}
	for (int i = size; i < size+N; i++) {
		cout << tree[i] << ' ';
	}
	cout << '\n';
}

void update(int n, int left, int right, int index, int val) {
	if (left == right) {
		
		//this means we are at the leaf node
		tree[n] = val;
		return;
	}
	if (left > right || left > index || right < index) return;
	int mid = (left+right)/2;
	update(n*2,left,mid,index,val);
	update(n*2,mid+1,right,index,val);
	//rechange the current node
	tree[n] = min(tree[n*2],tree[n*2+1]);
}

int query(int n, int left, int right, int i, int j) {
	//queries for [i,j] (INCLUSIVE)
	//queries for the sum
	if (j < left || right < i) {
		return INF;
	}
	if (i <= left && right <= j) {
		return tree[n];
	}
	int mid = (left+right)/2;
	int p1 = query(2*n,left,mid,i,j);
	int p2 = query(2*n+1,mid+1,right,i,j);
	return min(p1,p2);	
}

void updateRange(int n, int start, int end, int l, int r, int val) {
	if (lazy[n] != 0) {
		tree[n] += (end-start+1) * lazy[n];
		if (start != end) {
			lazy[n*2] += lazy[n];
			lazy[n*2+1] += lazy[n];
		}
		lazy[n] = 0;
	}
	if (start > end || start > r || end < l) {
		return;
	}
	if (start >= l && end <= r) {
		tree[n] += (end-start+1)*val;
		if (start != end) {
			lazy[n*2] += val;
			lazy[n*2+1] += val;
		}
		return;
	}
	int mid = (start+end)/2;
	updateRange(n*2,start,mid,l,r,val);
	updateRange(n*2+1,mid+1,end,l,r,val);
	tree[n] = tree[n*2] + tree[n*2+1];
}

int queryRange(int n, int start, int end, int l, int r) {
	if (start > end || start > r || end < l) {
		return 0;
	}
	if (lazy[n] != 0) {
		tree[n] += (end-start+1)*lazy[n];
		if (start != end) {
			lazy[n*2] += lazy[n];
			lazy[n*2+1] += lazy[n];
		}
		lazy[n] = 0;
	}
	if (start >= l && end <= r) {
		return tree[n];
	}
	int mid = (start+end)/2;
	int p1 = queryRange(n*2,start,mid,l,r);
	int p2 = queryRange(n*2+1,mid+1,end,l,r);
	return p1+p2;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("circularRMQ.in","r",stdin);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	build(1,0,N);
	int M; cin >> M;
	for (int i = 0; i < M; i++) {
		
	}

	
	

	
	return 0;
}

