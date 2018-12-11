/*
ID: silxikys
PROG: humble
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

//globals
int K, N;
int primes[100];
long humbles[100010];


int main() {
	t1 = gettime();
	ofstream fout("humble.out");
	ifstream fin("humble.in");

	fin >> K >> N;
	for (int i = 0; i < K; i++) {
		fin >> primes[i];
	}
	N++;

	humbles[0] = 1;
	int primeLast[100];
	for (int i = 0; i < K; i++) {
		primeLast[i] = 0;
	}
	for (int i = 0; i < N; i++) {
		long min = LONG_MAX;
		int pNext;
		for (int j = 0; j < K; j++) {
			long prod = primes[j]*humbles[primeLast[j]];
			if (prod < min) {
				min = prod;
				pNext = j;
			}
			else if (prod == min) {
				primeLast[j]++;
			}
		}
		humbles[i+1] = min;
		primeLast[pNext]++;
		/*
		cout << humbles[i+1] << " ";
		for (int a = 0; a < K; a++) {
			cout << humbles[primeLast[a]] << " ";
		}
		cout << endl;
		*/
	}

	cout << humbles[N-1] << endl;
	fout << humbles[N-1] << endl;

	
	endProgram(t1);
	return 0;
}