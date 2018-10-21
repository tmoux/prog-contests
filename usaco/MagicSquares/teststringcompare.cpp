/*
ID: silxikys
PROG: test
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




int main() {
	t1 = gettime();
	ofstream fout("test.out");
	ifstream fin("test.in");

	string a = "ABBBCABB";
	string b = "BBBACABB";
	cout << (a < b) << endl;



	
	endProgram(t1);
	return 0;
}