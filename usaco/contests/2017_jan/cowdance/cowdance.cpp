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
ifstream fin("2.in");

int N, tmax;
const int maxn = 10000;
int cows[maxn];
int arr[maxn] = {0};

bool minTime(int k, int cows[]) {
	priority_queue<int,vector<int>,greater<int>> que;
	int last = 0;
	for (int i = 0; i < N; i++) {
		if (que.size() == k) {
			last = que.top();
			que.pop();
		}
		if (last = cows[i] > tmax) {
			return false;
		}
		que.push(last+cows[i]);
	}
	return true;
}

int binarySearch(int cows[]) {
	int min = 1;
	int max = N;
	while (min != max) {
		int mid = (min+max)/2;
		if (minTime(mid,cows)) {
			max = mid;
		}
		else {
			min = mid+1;
		}
	}
	cout << minTime(min,cows) << '\n';
	return min;
}

int main()

{
	fin >> N >> tmax;
	for (int i = 0; i < N; i++) {
		fin >> cows[i];
	}

	sort(cows,cows+N,greater<int>());
	
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