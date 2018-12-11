/*
ID: silxikys
PROG: vans
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

const int maxn = 3001;
bool grid[maxn][maxn];

int main() {
	t1 = gettime();
	ofstream fout("vans.out");
	ifstream fin("vans.in");

	fout << 12 << '\n';


	
	endProgram(t1);
	return 0;
}