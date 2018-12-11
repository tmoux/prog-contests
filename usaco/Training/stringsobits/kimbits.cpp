/*
ID: silxikys
PROG: kimbits
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

int N, L, I; 

int numOnes(int n) {
	int c = 0;
	while(n) {
		if (n & 1) c++;
		n >>= 1;
	}

	return c;
}

string toString(int n) {
	string ret(N, '0');

	int index = N-1;
	while (n > 0) {
		if (n & 1) {
			ret[index] = '1';
		}
		n >>= 1;
		index--;
	}
	return ret;
}

int main() {
	t1 = gettime();
	ofstream fout("kimbits.out");
	ifstream fin("kimbits.in");

	fin >> N >> L >> I;
	int icounter = 0;
	for (int num = 0; num <= pow(2,N); num++) {
		if (numOnes(num) <= L) {
			icounter++;
			if (icounter == I) {
				cout << toString(num) << endl;
				fout << toString(num) << endl;

				break;
			}
		}
	}


	
	endProgram(t1);
	return 0;
}