/*
ID: silxikys
PROG: bigbrn
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

const int maxn = 1005;
int N, T;
int field[maxn][maxn]; //1 = blocked, 0 is empty


int main() {
	t1 = gettime();
	ofstream fout("bigbrn.out");
	ifstream fin("bigbrn.in");

	fin >> N >> T;
	for (int i = 0; i < T; i++) {
		int x, y;
		fin >> x >> y;
		field[x][y] = 1;
	}

	int longest = 1;
	for (int length = 2; length <= N; length++) {
		int squaresfound = 0;
		for (int i = 1; i + length <= N + 1; i++) {
			for (int j = 1; j + length <= N + 1; j++) {
				field[i][j] = (field[i][j] |
							   field[i][j+1] |
							   field[i+1][j] |
							   field[i+1][j+1]);
				if (!field[i][j]) {
					longest = length;
					squaresfound++;
				}
			}
		}
		if (squaresfound < 4) {
			break;
		}
	}

	cout << longest << endl;
	fout << longest << endl;
	
	endProgram(t1);
	return 0;
}