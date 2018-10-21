/*
ID: silxikys
PROG: fact4
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


int rightmost(int n) {
	while (n % 10 == 0) {
		n /= 10;
	}
	return n % 1000;
}

int fact(int n) {
	if (n == 1) return 1;
	return rightmost(rightmost(n)*fact(n-1));
}

int main() {
	t1 = gettime();
	ofstream fout("fact4.out");
	ifstream fin("fact4.in");

	int N; fin >> N;
	cout << fact(N) << endl;
	fout << (fact(N) % 10) << endl;


	
	endProgram(t1);
	return 0;
}