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
const int MAXN = 10000;
int stamps[50];
vector<pair<int,int>> lastSeen;

bool addCent(int m, int k) {
	if (m <= stamps[N-1]) {
		for (int i = 0; i < N; i++) {
			if (m-stamps[i] == 0) {
				lastSeen.push_back(make_pair(m,1));
				return true;
			}
		}
	}
	for (int i = N-1; i >= 0; i--) {
		int minpSecond = INT_MAX;
		for (pair<int,int> p: lastSeen) {
			if (p.first == m - stamps[i] && p.second < k && p.second < minpSecond) {
				minpSecond = p.second;
			}
		}
		if (minpSecond < INT_MAX) {
			lastSeen.push_back(make_pair(m,minpSecond+1));
			return true;
		}
	}
	return false;
}


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
	for (int i = 0; i < N; i++) {
		cout << stamps[i] << " ";
	}
	cout << endl;
	
	int M = 1;
	while (addCent(M,K)) {
		M++;
		if (M > stamps[N-1] + 1) {
			lastSeen.erase(lastSeen.begin());
		}
		/*
		for (pair<int,int> p: lastSeen) {
			cout << p. first << " " << p.second << endl;
		}
		cout << endl;
		*/
		if (M == 248) {
			for (pair<int,int> p: lastSeen) {
				cout << p. first << " " << p.second << endl;
			}
		}
	}
	cout << M-1 << endl;
	fout << M-1 << endl;

	
	
	endProgram(t1);
	return 0;
}