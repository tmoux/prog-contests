/*
ID: silxikys
PROG: charrec
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


const int letterlength = 20;
const int maxn = 1205;
char alphabet[540][letterlength];
char corrupted[maxn][letterlength];
char repr[27] = {'_','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int lossline(int i, int j) {
	int total = 0;
	for (int k = 0; k < 20; k++) {
		if (alphabet[i][k] != corrupted[j][k]) {
			total++;
		}
	}
	return total;
}

pair<int, int> lossforChar(int i, int start, int end) {
	int minloss = 999999999;
	int startnxtline;

	i *= 20;
	//one line is missing
	if (end - start >= 19) {
		for (int skip = i; skip < i + 20; skip++) {
			int loss = 0;
			int checkline = start;
			for (int line = 0; line < 20; line++) {
				if (i + line != skip) {
					loss += lossline(i + line, checkline);
					checkline++;
				}
			}
			if (loss < minloss) {
				minloss = loss;
				startnxtline = start + 19;
			}
		}
	}


	return make_pair(minloss,startnxtline);
}

char recognize(int start, int end) {
	int leastloss = 99999999;
	int leastchar;
	int startnxtline;
	for (int i = 0; i < 27; i++) {
		pair<int, int> p = lossforChar(i, start, end);
		if (p.first < leastloss) {
			leastloss = p.first;
			leastchar = i;
			startnxtline = p.second;
		}
	}
	return repr[leastchar];
}

int main() {
	t1 = gettime();
	ofstream fout("charrec.out");
	ifstream fin("charrec.in");
	ifstream fonts("font.in");

	//input
	int n; fonts >> n;
	for (int i = 0; i < n; i++) {
		string s;
		fonts >> s;
		for (int j = 0; j < letterlength; j++) {
			alphabet[i][j] = s[j];
		}
	}

	/*
	for (int i = 0; i < 540; i++) {
		for (int j = 0; j < letterlength; j++) {
			cout << alphabet[i][j];
		} cout << '\n';
	}
	*/

	fin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		fin >> s;
		for (int j = 0; j < letterlength; j++) {
			corrupted[i][j] = s[j];
		}
	}

	pair<int, int> p = lossforChar(1,0,19);
	cout << p.first << '\n' << p.second << '\n';



	


	
	endProgram(t1);
	return 0;
}