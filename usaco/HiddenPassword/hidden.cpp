/*
ID: silxikys
PROG: hidden
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

int L;
char S[100001];


int main() {
	t1 = gettime();
	ofstream fout("hidden.out");
	ifstream fin("hidden.in");

	//input
	fin >> L;
	string s;
	int index = 0;

	for (int i = 0; i < L / 72 + 1; i++) {
		fin >> s;
		for (int j = 0; j < s.length(); j++) {
			S[index] = s[j];
			index++;
		}
	}

	
	int bestsofar = 0;
	for (int index = 1; index < L; index++) {
		bool comparable = true;
		for (int i = 0; i < L && comparable; i++) {
			if (S[(index + i) % L] < S[(bestsofar + i) % L]) {
				break;
			}
			else if (S[(index + i) % L] > S[(bestsofar + i) % L]) {
				comparable = false;
			}
		}
		if (comparable) {
			bestsofar = index;
		}
	}

	cout << bestsofar << '\n';
	fout << bestsofar << '\n';
	
	
	endProgram(t1);
	return 0;
}