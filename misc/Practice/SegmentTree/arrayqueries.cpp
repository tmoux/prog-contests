#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stdio.h>
using namespace std;

const int maxn = 1000001;
const int INF = 999999999;

int arr[maxn];
int N, Q, T;
int tree[4*maxn];

struct SegTree 
{
	void build(int n=1, int left=0, int right=N) {
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

	void update(int index, int val, int n=1, int left=0, int right = N) {
		if (left == right) {
			//this means we are at the leaf node
			tree[n] = val;
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
			tree[n] = min(tree[n*2],tree[n*2+1]);
		}
		//rechange the current node
		
	}

	int query(int i, int j, int n=1, int left=0, int right=N) {
		//queries for [i,j] (INCLUSIVE)
		//queries for the sum
		if (left > right || j < left || right < i) {
			return INF;
		}
		if (i <= left && right <= j) {
			//cout << left << ' ' << right << ' ' << n << '\n';
			return tree[n];
		}
		int mid = (left+right)/2;
		int p1 = query(i,j,2*n,left,mid);
		int p2 = query(i,j,2*n+1,mid+1,right);
		return min(p1,p2);	
	}

} segtree;


int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("arrayqueries.in","r",stdin);
	scanf("%d",&T);
	for (int a = 0; a < T; a++) {
		
		for (int i = 0; i < maxn; i++) {
			arr[i] = INF;
		}
		for (int i = 0; i < 4*maxn; i++) {
			tree[i] = INF;
		}
		
		scanf("%d", &N);
		scanf("%d", &Q);
		for (int i = 0; i < N; i++) {
			scanf("%d",&arr[i]);
		}
		
		segtree.build();
		for (int i = 0; i < 32; i++) {
			//cout << tree[i] << '\n';
		}
		
		cout << "Case " << (a+1) << ":\n";
		for (int ss = 0; ss < Q; ss++) {
			int i, j; scanf("%d %d",&i,&j);
			printf("%d\n",segtree.query(i-1,j-1));
		}
		
		//cout << segtree.query(4,4) << '\n';
	}
	
	return 0;
}

