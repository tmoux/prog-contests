#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 1000001;
int tree[4*maxn];
int lazy[4*maxn];
int arr[maxn];
int N, M;

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
	tree[n] = tree[n*2] + tree[n*2+1];
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
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	build(1,0,N);
	cin >> M;
    while (M--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            cout << queryRange(1,1,N,l,r) << '\n';
        }
        else {
            ll x; cin >> x;
            updateRange(1,1,N,l,r,x); 
        }
    }

	
	return 0;
}


