/*
ID: silxikys
PROG: theme
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

int N;
const int maxn = 3000;
int notes[maxn];
int diffs[maxn];
bool themes[maxn][maxn];

int main() {
	t1 = gettime();
	ofstream fout("theme.out");
	ifstream fin("theme.in");

	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> notes[i];
		if (i > 0) {
			diffs[i] = notes[i]-notes[i-1];
		}
	}

	int longTheme = 0;
	//create themes array with minimum length 5 (4 in diffs)
	for (int i = 1; i < N - 4; i++) {
		vector<int> seq;

		for (int a = i; a < i + 4; a++) {
			seq.push_back(diffs[a]);
		}
		/*
		for (int a: seq) {
			cout << a << ' ';
		} cout << '\n';
		*/
		for (int j = i + 4; j < N - 4; j++) {
			vector<int> seq2;
			for (int a = j; a < j + 4; a++) {
				seq2.push_back(diffs[a]);
			}
			if (seq == seq2) {
				themes[i][j] = 1;
				longTheme = 4;
			}
		}
	}
	/*
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < N; j++) {
			cout << themes[i][j];
		} cout << '\n';
	}
	*/


	for (int length = 5; length < N / 2 + 1; length++) {
		bool streak = false;
		for (int i = 1; i < N; i++) {
			for (int j = i; j < N; j++) {
				if (themes[i][j]) {
					if (i + length < N && j + length < N) {
						if (diffs[i+length] != diffs[j+length]) {
							themes[i][j] = 0;
						}
						else {
							streak = true;
						}
					}
					else {
						themes[i][j] = 0;
					}
				}
			}
		}
		if (streak) {
			longTheme = length;
		}
	}

	cout << (longTheme+1) << '\n';
	fout << (longTheme+1) << '\n';

	endProgram(t1);
	return 0;
	
	
}