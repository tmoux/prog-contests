/*
ID: silxikys
PROG: sprime
LANG: C++11
*/

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>
//#include <ctime>
#include <array>
#include <chrono>
#include <math.h>
using namespace std;
using namespace std::chrono;

int sprimes[1000];
int index = 0;

bool isPrime(int n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (n / 2 == n / 2.0) return false;
	for (int i = 3; i <= sqrt(n); i += 2) {
		if (n % i == 0) return false;
	}
	return true;
}

void findSPrime(int num, int currLength, int maxLength) {

	if (currLength == maxLength) {
		sprimes[index] = num;
		index++;
	}
	else {
		for (int i = 1; i < 10; i += 2) {
			int newNum = 10 * num + i;
			if (isPrime(newNum)) {
				findSPrime(newNum, currLength + 1, maxLength);

			}
		}
	}
	
}

int main()
{
	//int start_s=clock();
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	//sprimes[10000] = -1;
	ofstream fout("sprime.out");
	ifstream fin("sprime.in");

	int N; fin >> N;
	//N = 2;
	int oneDigitPrimes[] = { 2,3,5,7 };
	for (int i = 0; i < 4; i++) {
		findSPrime(oneDigitPrimes[i], 1, N);
	}
	for (int i = 0; i < index; i++) {
		fout << sprimes[i] << endl;
		cout << sprimes[i] << endl;
	}

	fin.close();
	fout.close();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(t2 - t1).count() / 1000000000.0;
	cout << "Execution time: " << duration << " seconds" << endl;
	
	//int stop_s = clock();
	//cout << "Execution time: " << (stop_s-start_s)/(double) CLOCKS_PER_SEC << " seconds" << endl;
	return 0;
}
