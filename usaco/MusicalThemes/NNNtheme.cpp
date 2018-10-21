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
const int maxn = 5000;
int notes[maxn];


int main() {
	t1 = gettime();
	ofstream fout("theme.out");
	ifstream fin("theme.in");

	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> notes[i];
	}

	int longest = 0;
	for (int i = 0; i < N; i++) {
		int streak = 1;
		for (int j = 0; N-2-j-i >= 0; j++) {
			if (notes[N-2-j]-notes[N-1-j] == 
				notes[N-2-j-i]-notes[N-1-j-i]) {
				streak = min(streak + 1, i);
			}
			else {
				streak = 1;
			}
			longest = max(longest,streak);
		}
	}

	cout << longest << endl;
	fout << ((longest >= 5) ? longest : 0) << '\n';
	

	endProgram(t1);
	return 0;
	
	
}