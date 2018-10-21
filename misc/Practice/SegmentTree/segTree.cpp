#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 10000;
int tree[3*maxn];
int arr[maxn];
int N;

void build(int n, int left, int right) {
	if (left > right) return;
	else if (left == right) {
		tree[n] = arr[left];
		return;
	}
	build(n*2,left,(left+right)/2);
	build(n*2+1,(left+right)/2+1,right);
	//the tree stores the sum of the child nodes,
	//but can be max or any operation I guess
	tree[n] = tree[n*2] + tree[n*2+1];
}

void update(int n, int left, int right, int index, int val) {
	if (left > right || left > index || right < index) return;
	if (left == right) {
		
		//this means we are at the leaf node
		tree[n] = val;
		return;
	}
	update(n*2,left,(left+right)/2,index,val);
	update(n*2,(left+right)/2+1,right,index,val);
	//rechange the current node
	tree[n] = tree[n*2] + tree[n*2+1];
}

int query(int n, int left, int right, int i, int j) {
	//queries for [i,j] (INCLUSIVE)
	//queries for the sum
	if (left > right || left > j || right < i) return 0;
	if (i <= left && right <= j) return tree[n];
	 
	int mid = (left+right)/2;
	return query(n*2,left,mid,i,j) + query(n*2+1,mid+1,right,i,j);
}

void printArray() {
	int size = 1;
	for (; size < N; size <<= 1) {}
	for (int i = size; i < size+N; i++) {
		cout << tree[i] << ' ';
	}
	cout << '\n';
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("input.in","r",stdin);
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	build(1,0,N-1);
	printArray();
	cout << query(1,0,N-1,0,2) << '\n';
	update(1,0,N-1,0,19);
	printArray();
	cout << query(1,0,N-1,0,2) << '\n';
	
	return 0;
}

