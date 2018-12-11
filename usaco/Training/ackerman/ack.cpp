/*
ID: silxikys
PROG: ack
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

int memo[10][10];

int ack(int m, int n) {
	//if (memo[m][n] != -1) return memo[m][n];
	if (m == 0) return memo[m][n] = n+1;
	if (m > 0 && n == 0) return memo[m][n] = ack(m-1,1);
	if (m > 0 && n > 0) return memo[m][n] = ack(m-1,ack(m,n-1));
}


int main() {
	t1 = gettime();
	ofstream fout("ack.out");
	ifstream fin("ack.in");

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			memo[i][j] = -1;
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cout << "ack of " << i << ", " << j << " = " << ack(i,j) << endl;
		}
	}



	
	endProgram(t1);
	return 0;
}