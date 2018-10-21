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
//char S[100001];


int main() {
	t1 = gettime();
	ofstream fout("hidden.out");
	ifstream fin("hidden.in");

	//input
	fin >> L;
	string s;
	char c;
	bool allsame = true;
	int index = 0;

	string S = "";
	for (int i = 0; i < (L - 1) / 72 + 1; i++) {
		fin >> s;
		if (i == 0) {
			c = s[0];
		}
		for (int j = 0; j < s.length(); j++) {

			if (allsame) {
				if (c != s[j]) {
					allsame = false;
				}
			}
		}
		S += s;
	}

	S += S;

	if (allsame) {
		cout << 0 << '\n';
		fout << 0 << '\n';
		return 0;
	}

	int i = 0, j = 1;
	while (j < L) {
		int c = 0;
		while (j + c < 2*L && S[i + c] == S[j + c]) {
			c++;
		}
		if (j + c == 2*L) {
			break;
		}
		if (S[i+c] > S[j+c]) {
			i = j;
			j = i + 1;
		}
		else {
			if (c == 0) {
				c = 1;
			}
			j += c;
		}
	}
	
	cout << i << endl;
	fout << i << '\n';
	endProgram(t1);
	return 0;
}