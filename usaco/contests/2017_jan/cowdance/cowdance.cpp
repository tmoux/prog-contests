/*
ID: silxikys
PROG: cowdance
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <queue>
using namespace std;

ofstream fout("cowdance.out");
ifstream fin("cowdance.in");

int N, tmax;
const int maxn = 10000;
int cows[maxn];
int arr[maxn];

bool minTime(int k, int cows[]) {
	priority_queue<int,vector<int>,greater<int>> que;
	int last = 0;
	for (int i = 0; i < N; i++) {
		if (que.size() == k) {
			last = que.top();
			que.pop();
		}
		if (last + cows[i] > tmax) {
			return false;
		}
		que.push(last+cows[i]);
	}
	return true;
}

int binarySearch(int cows[]) {
	int min = 0;
	int max = N;
	while (min + 1 < max) {
		int mid = (min+max)/2;
		if (minTime(mid,cows)) {
			max = mid;
		}
		else {
			min = mid;
		}
	}
	return max;
}

int main()

{
	fin >> N >> tmax;
	for (int i = 0; i < N; i++) {
		fin >> cows[i];
	}

	//sort(cows,cows+N,greater<int>());
	
	int ans = binarySearch(cows);
	cout << ans << '\n';
	fout << ans << '\n';
	
	
  /*
	for (int i = 1; i < 5; i++) {
		cout << i << ' ' << minTime(i,cows) << '\n';
	}
  */

	return 0;
}
