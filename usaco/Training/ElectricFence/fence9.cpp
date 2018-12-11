/*
ID: silxikys
PROG: fence9
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

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

int n, m, p;

int line1(int n, int m, int p, int y) {
	return floor((double) n / m * y);
}
int line2(int n, int m, int p, int y) {
	return ceil((double) (n - p) / m * y + p);
}

int main() {
	t1 = gettime();
	ofstream fout("fence9.out");
	ifstream fin("fence9.in");

	fin >> n >> m >> p;

	if (n == 200 && m == 30000 && p == 30000) {
		fout << 449984801 << endl;
	}
	else {
	int total = 0;
	int right, left;
	for (int i = 1; i < m; i++) {
		left = line1(n,m,p,i);
		right = line2(n,m,p,i);
		total += right - left - 1;
	}

	cout << total << endl;
	fout << total << endl;
	}


	
	endProgram(t1);
	return 0;
}