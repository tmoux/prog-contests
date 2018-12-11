/*
ID: silxikys
PROG: range
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

int field[252][252];
int oldsquares[252][252];
int newsquares[252][252];




int main() {
	t1 = gettime();
	ofstream fout("range.out");
	ifstream fin("range.in");

	//input
	int N; fin >> N;
	string line;
	for (int i = 0; i < N; i++) {
		fin >> line;
		for (int j = 0; j < N; j++) {
			field[i][j] = line[j] - '0';
		}
	}

	for (int i = 2; i <= N; i++) {
		int count = 0;
		for (int j = 0; j < N - i + 1; j++) {
			for (int k = 0; k < N - i + 1; k++) {
				if (i == 2) {
					newsquares[j][k] = field[j][k] & field[j][k+1] & field[j+1][k] & field[j+1][k+1];
					if (newsquares[j][k]) {
						count++;
					}
				}
				else {
					newsquares[j][k] = oldsquares[j][k] & oldsquares[j][k+1] & oldsquares[j+1][k] & oldsquares[j+1][k+1];
					if (newsquares[j][k]) {
						count++;
					} 
				}
			}
		}
		for (int j = 0; j < N - i + 1; j++) {
			for (int k = 0; k < N - i + 1; k++) {
				oldsquares[j][k] = newsquares[j][k];
			}
		}
		if (count > 0) {
			cout << i << " " << count << endl;
			fout << i << " " << count << endl;
		}
	}


	
	

	
	endProgram(t1);
	return 0;
}