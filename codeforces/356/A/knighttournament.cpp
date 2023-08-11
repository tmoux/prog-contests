#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stdio.h>
using namespace std;

const int maxn = 300005;

int N, M;
int arr[maxn];
int st[4*maxn];

void build(int p, int l, int r) {
	if (l == r) {st[p] = 0; return;};
	build(p*2,l,(l+r)/2);
	build(p*2+1,(l+r)/2+1,r);
	st[p] = 0;
	return;
}

void update(int val, int i, int j, int p = 1, int l = 0, int r = N-1) {
	if (i > r || j < l) {return;};
	if (l >= i && r <= j) {
		if (st[p] == (r-l)+1) {return;}
		if (l==r) {arr[l]=val, st[p] = 1; return;}
	}
	update(val,i,j,p*2,l,(l+r)/2);
	update(val,i,j,p*2+1,(l+r)/2+1,r);
	st[p]=st[p*2]+st[p*2+1];
	return;
}


int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("knight.in","r",stdin);
	cin >> N >> M;
	build(1,0,N-1);
	
	for (int aa = 0; aa < M; aa++) {
		int i, j, k;
		cin >> i >> j >> k;
		int i1 = i-1, j1 = k-2, i2 = k, j2 = j-1;
		if (i1 <= j1) {
			update(k,i1,j1);
		}
		if (i2 <= j2) {
			update(k,i2,j2);
		}


	}
	for (int i = 0; i < N; i++) {
		cout << (arr[i]+1) << ' ';
	}
	cout << '\n';
	
	
	return 0;
}

