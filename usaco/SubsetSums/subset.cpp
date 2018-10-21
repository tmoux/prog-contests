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

int numberOfSums(int n, int k) {
	if (n > k*(k+1)/2) return 0;
	if (n == 0) return 1;
	return numberOfSums(n,k-1) + numberOfSums(n-k,k-1);
}

int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("subset.out");
	ifstream fin("subset.in");
	
	cout << numberOfSums(7,14);

	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}