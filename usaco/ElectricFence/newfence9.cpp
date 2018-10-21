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

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
	t1 = gettime();
	ofstream fout("fence9.out");
	ifstream fin("fence9.in");

	fin >> n >> m >> p;

	int doublearea = m*p;
	int boundaries = 0;
	boundaries += gcd(n,m);
	boundaries += gcd(m,abs(n-p));
	boundaries += gcd(p,0);
	//cout << doublearea << endl;

	int ans = (doublearea - boundaries)/2 + 1;
	cout << ans << endl;
	fout << ans << endl;



	
	endProgram(t1);
	return 0;
}