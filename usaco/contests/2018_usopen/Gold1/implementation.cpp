/*
ID: silxikys
PROG: sort
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;

ofstream fout("sort.out");
ifstream fin("sort.in");

const int maxn = 100001;
int N, A[maxn];

void bsort(int l, int r) {
	for (int i = l; i < r; i++) {
		if (A[i+1] < A[i]) {
			swap(A[i],A[i+1]);
		}
	}
	for (int i = r-1; i >= l; i--) {
		if (A[i+1] < A[i]) {
			swap(A[i],A[i+1]);
		}
	}
}

int main() 
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> A[i];
	}

	int ans = 0;
	bool sorted = false;
	int l = 0, r = N-1;
	while (!sorted) {
		sorted = true;
		ans++;
		bsort(l,r);
		while (l < N-1 && A[l] < A[l+1]) {
			l++;
		}
		while (r > 0 && A[r] > A[r-1]) {
			r--;
		}
		if (l < r) {
			sorted = false;
		}
	}
	cout << ans << '\n';
	fout << ans << '\n';

	return 0;
}