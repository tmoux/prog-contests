/*
ID: silxikys
PROG: stamps
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
#include <array>
#include <chrono>
#include <math.h>
#include <cstring>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

int N, K;
const int MAXN = 2000010;
int stamps[50];
int dp[MAXN];


int main() {
	t1 = gettime();
	ofstream fout("stamps.out");
	ifstream fin("stamps.in");

	//input
	fin >> K >> N;
	for (int i = 0; i < N; i++) {
		fin >> stamps[i];
	}
	sort(stamps,stamps+N);
	
	for (int i = 1; i < MAXN; i++) {
		//dp[i] = INT_MAX;
		int mini = INT_MAX;
		int minfrom;
		for (int j = 0; j < N; j++) {
			if (i - stamps[j] < 0) {
				continue;
			}
			if (dp[i-stamps[j]]+1 < mini) {
				mini = dp[i-stamps[j]]+1;
				minfrom = i-stamps[j];
			}
		}
		dp[i] = mini;
		cout << i << " " << minfrom << endl;
		if (dp[i] > K) {
			cout << i-1 << endl;
			fout << i-1 << endl;
			break;
		}
	}

	
	
	endProgram(t1);
	return 0;
}