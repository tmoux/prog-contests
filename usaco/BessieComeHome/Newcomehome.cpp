/*
ID: silxikys
PROG: comehome
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

//globals
const int MAXC = 52;
int sp[MAXC][MAXC];
int P;


int charInt(char c) {
	if (toupper(c) == c) {return c-65;}
	return c-71;
}

char intChar(int i) {
	if (i < 26) {return (char)(i+65);}
	return (char)(i+71);
}

int main() {
	t1 = gettime();
	ofstream fout("comehome.out");
	ifstream fin("comehome.in");

	for (int i = 0; i < MAXC; i++) {
		for (int j = 0; j < MAXC; j++) {
			sp[i][j] = 500000;
		}
	}

	//initializes all values of sp
	fin >> P;
	for (int i = 0; i < P; i++) { 
		char a, b; int c; fin >> a >> b >> c;
		sp[charInt(a)][charInt(b)] = min(sp[charInt(a)][charInt(b)],c);
		sp[charInt(b)][charInt(a)] = sp[charInt(a)][charInt(b)];
	}



	//floyd-warshall
	for (int k = 0; k < MAXC; k++) {
		for (int i = 0; i < MAXC; i++) {
			if (sp[i][k] + sp[k][25] < sp[i][25]) {
				sp[i][25] = sp[i][k] + sp[k][25];
			}
		}
	}
	
	for (int i = 0; i < MAXC; i++) {
		for (int j = 0; j < MAXC; j++) {
			cout << sp[i][j] << " ";
		}
		cout << endl;
	}
	
	int minZ = INT_MAX;
	int minChar;
	for (int i = 0; i < charInt('Z'); i++) {
		int dist = sp[i][charInt('Z')];
		if (dist < minZ) {
			minZ = dist;
			minChar = i;
		}
	}

	cout << intChar(minChar) << " " << minZ << endl;
	fout << intChar(minChar) << " " << minZ << endl;


	
	endProgram(t1);
	return 0;
}