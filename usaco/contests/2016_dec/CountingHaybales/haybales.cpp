/*
ID: silxikys
PROG: haybales
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

ofstream fout("haybales.out");
ifstream fin("haybales.in");

const int maxn = 100000;
int N, Q;
int haybales[maxn];

int findLow(int arr[], int i, int l, int r) {
	if (l <= r) {
		int mid = (r + l)/2;
		if (arr[mid] == i) {
			return mid;
		}
		if (arr[mid] < i) {
			return findLow(arr,i,mid+1,r);
		}
		return findLow(arr,i,l,mid-1);
	}
	return l;
}

int findHigh(int arr[], int i, int l, int r) {
	if (l <= r) {
		int mid = (r + l)/2;
		if (arr[mid] == i) {
			return mid;
		}
		if (arr[mid] < i) {
			return findHigh(arr,i,mid+1,r);
		}
		return findHigh(arr,i,l,mid-1);
	}
	return r;
}

void printQuery(int A, int B) {
	int start = findLow(haybales,A,0,N-1);
	int end = findHigh(haybales,B,0,N-1);
	int ans;
	if (A > haybales[N-1] || B < haybales[0]) {
		ans = 0;
	}
	else {
		ans = end - start + 1;
	}
	cout << A << ' ' << B << ' ' << ans << '\n';
	cout << start << ' ' << end << '\n';
	fout << ans << '\n';
}

int main() {

	fin >> N >> Q;
	for (int i = 0; i < N; i++) {
		fin >> haybales[i];
	}
	sort(haybales,haybales+N);

	for (int i = 0; i < Q; i++) {
		int A, B;
		fin >> A >> B;
		printQuery(A,B);
	}


	return 0;
}