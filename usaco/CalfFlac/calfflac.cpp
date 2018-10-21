/*
ID: silxikys
PROG: calfflac
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

const int maxn = 20001;
const int maxp = 2000;

int main() {
	t1 = gettime();
	ofstream fout("calfflac.out");
	ifstream fin("calfflac.in");

	//input
	string original = "";
	char letters[maxn];
	int lmap[maxn];
	string s;
	while(getline(fin,s)) {
		original += s;
		original += '\n';
	}

	int lcount = 0;
	for (int i = 0; i < original.size(); i++) {
		if (isalpha(original[i])) {
			lmap[lcount] = i;
			letters[lcount++] = tolower(original[i]);
		}
	}

	//calculate odd and even palindromes
	int longestpali = -1;
	int starti, endi;

	for (int i = 0; i < lcount; i++) {
		//odd palindromes
		int oddlength = 0;
		while (i-oddlength >= 0 && i+oddlength < lcount &&
				letters[i-oddlength] == letters[i+oddlength]) {
			oddlength++;
		}
		oddlength--;

		int palilength = oddlength * 2 + 1;
		if (palilength > longestpali) {
			longestpali = palilength;
			starti = i - oddlength;
			endi = i + oddlength;
		}

		//even palindromes
		int evenlength = 0;
		while (i-evenlength >= 0 && i+evenlength+1 < lcount &&
				letters[i-evenlength] == letters[i+evenlength+1]) {
			evenlength++;
		}
		evenlength--;

		palilength = (evenlength + 1) * 2;
		if (palilength > longestpali) {
			longestpali = palilength;
			starti = i - evenlength;
			endi = i + evenlength + 1;
		}

	}

	//output
	cout << longestpali << '\n';
	for (int i = lmap[starti]; i <= lmap[endi]; i++) {
		cout << original[i];
	}
	cout << '\n';

	fout << longestpali << '\n';
	for (int i = lmap[starti]; i <= lmap[endi]; i++) {
		fout << original[i];
	}
	fout << '\n';
	endProgram(t1);
	return 0;
}