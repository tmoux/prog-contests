/*
ID: silxikys
PROG: diamond
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

ofstream fout("diamond.out");
ifstream fin("diamond.in");

const int maxn = 50000;
int diamonds[maxn];
int N, K;


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
	return r;
}

int main() 
{
	fin >> N >> K;
	for (int i = 0; i < N; i++) {
		fin >> diamonds[i];
	}
	
	sort(diamonds,diamonds+N);
	int strek[maxn];
	for (int i = 0; i < N; i++) {
		strek[i] = findLow(diamonds,diamonds[i]+K,0,N-1) - i + 1;
		//cout << i << ' ' << strek[i] << '\n';
	}

	int ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			int length = strek[i] + strek[j];
			if (i + strek[i] - 1 >= j) {
				length -= i + strek[i] - j;
			}
			ans = max(ans,length);
		}
	}

	cout << ans << '\n';
	fout << ans << '\n';

	


	return 0;
}