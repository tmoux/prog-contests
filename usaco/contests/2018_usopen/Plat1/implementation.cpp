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
#include <set>
using namespace std;
typedef pair<int,int> pii;

ofstream fout("sort.out");
ifstream fin("sort.in");

int N;
const int maxn = 100001;
int A[maxn];
int ans = 0;

void bubble_sort_pass(int i, int j) {
	for (int k = i; k < j-1; k++) {
		if (A[k] > A[k+1]) {
			swap(A[k],A[k+1]);
		}
	}
}

void count_work(int i, int j) {
	//cout << i << ' ' << j << '\n';
	//interval from [i,j)
	if (i == j-1) {
		return;
	}
	ans += (j-i);
	bubble_sort_pass(i,j);
	multiset<int> nums;
	vector<pii> partitions;
	for (int k = i; k < j; k++) {
		nums.insert(A[k]);
	}

	int l = i, r = i;
	for (; r < j; r++) {
		int first = *nums.begin();
		auto itr = nums.find(A[r]);
		if (itr != nums.end()) {
		    nums.erase(itr);
		}
		
		if (A[r] == first) {
			partitions.push_back({l,r+1});
			l = r + 1;
		}
		
	}
	for (pii p: partitions) {
		count_work(p.first,p.second);
	}
}

int main() 
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> A[i];
	}
	count_work(0,N);
	cout << ans << '\n';
	fout << ans << '\n';
	return 0;
}