/*
ID: silxikys
PROG: nocows
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

//globals
const int MAX_N = 200;
const int MAX_K = 100;
const int MOD = 9901;
long cache[MAX_N][MAX_K];

int mod(int n, int b) {
	while (n < 0) {
		n += b;
	}
	return n % b;
}

long pedigree(int n, int k) {
	if (cache[n][k] != -1) {
		return cache[n][k];
	}
	int sum = 0;
	for (int i = 1; i<n;i+=2) {
		if (i <= pow(2,k-1) && n-1-i <= pow(2,k-1)) {
			sum = (sum +(pedigree(i,k-1)*pedigree(n-1-i,k-1))) % MOD;
		}
	}
	//cache[n][k] = sum % MOD;
	cache[n][k] = sum;
	return cache[n][k];
}

int main() {
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	ofstream fout("nocows.out");
	ifstream fin("nocows.in");

	//fill cache
	for (int i = 0; i<=MAX_N;i++) {
		for (int j = 0; j<MAX_K;j++) {
			if (i == 1 || i == 3) {
				cache[i][j] = 1;
			}
			else {
				cache[i][j] = -1;
			}
		}
	}

	int N, K; fin >> N >> K;
	long combinations = mod((pedigree(N,K) - pedigree(N,K-1)),MOD);

	cout << combinations << endl;
	fout << combinations << endl;

	/*
	for (int i = 0; i < 178; i++) {
		for (int j = 0; j<58;j++) {
			if (cache[i][j] > 0) {
				cout << " " << cache[i][j] << " ";
			}
			else {
				 cout << cache[i][j] << " ";
			}
			
		}
		cout << endl;
	}
	*/
	
	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2-t1).count()/1000000000.0;
	cout << endl << "Execution time: " << duration << " seconds" << endl;
	return 0;
}