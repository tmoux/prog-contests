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
int make[20000][200];
int stamps[50];

int canMake(int n, int k) {
	if (k < 0 || n < 0) return -1;
	if (make[n][k] != 0) return make[n][k];
	int a = -1;
	for (int i = 0; i < N; i++) {
		a = max(canMake(n-stamps[i],k-1),a);
		if (a == 1) {
			break;
		}
	}
	return make[n][k] = a;
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

	//initialize make array
	//memset(make, -1, sizeof(make));
	for (int i = 0; i < 200; i++) {
		make[0][i] = 1;
	}

	//continue until largest
	int M = 1;
	while (canMake(M,K) == 1) {
		M++;
	}
	cout << M-1 << endl;
	fout << M-1 << endl;
	

	
	endProgram(t1);
	return 0;
}