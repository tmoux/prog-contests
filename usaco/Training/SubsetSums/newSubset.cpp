/*
ID: silxikys
PROG: subset
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
using namespace std;
using namespace std::chrono;

long long nsLookup[800][40];

int arithmeticSum(int n) {
	return n*(n+1)/2;
}

long long numberOfSums(int n, int k) {
	if (n < 0 || k < 0) return 0;
	if (nsLookup[n][k] != -1) return nsLookup[n][k];
	if (n == 0) return nsLookup[n][k] = 1;
	return nsLookup[n][k] = numberOfSums(n,k-1) + numberOfSums(n-k,k-1);
}

int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("subset.out");
	ifstream fin("subset.in");
	
	int N; fin >> N;
	
	for (int n = 0; n < 800; n++) {
		for (int k = 0; k<40;k++) {
			nsLookup[n][k] = -1;
		}
	}
	
	int as = arithmeticSum(N);
	if (as % 2 == 1) {
		cout << 0 << endl;
		fout << 0 << endl;
	}
	else {
		long long ans = numberOfSums(as/2,N)/2;
		//if (ans < 0) {
		//	ans += 2147483648;
		//}
		cout << ans << endl;
		fout << ans << endl;
	}

	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}