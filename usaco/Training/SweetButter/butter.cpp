/*
ID: silxikys
PROG: butter
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
int N, P, C;
const int maxp = 805;
const int inf = 1000;
int sp[maxp][maxp];
int cowAt[maxp];


int main() {
	t1 = gettime();
	ofstream fout("butter.out");
	ifstream fin("butter.in");

	//input
	fin >> N >> P >> C;
	for (int i = 0; i < N; i++) {
		fin >> cowAt[i];
	}
	for (int i = 0; i < C; i++) {
		int a, b, c; fin >> a >> b >> c;
		sp[a][b] = c;
		sp[b][a] = c;
	}
	/*
	for (int i = 1; i <= P; i++) {
		for (int j = 1; j <= P; j++) {
			cout << sp[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < N; i++) {
		cout << cowAt[i] << endl;
	}
	*/
	for (int i = 1; i <= P; i++) {
		for (int j = 1; j <= P; j++) {
			if (i != j && sp[i][j] == 0) {
				sp[i][j] = inf;
			}
		}
	}
	//floyd-warshall
	for (int k = 1; k <= P; k++) {
		for (int i = 1; i <= P; i++) {
			for (int j = 1; j <= P; j++) {
				if (sp[i][j] > sp[i][k]+sp[k][j]) {
					sp[i][j] = sp[i][k]+sp[k][j];
				}
			}
		}
	}
	/*
	for (int i = 1; i <= P; i++) {
		for (int j = 1; j <= P; j++) {
			cout << sp[i][j] << " ";
		}
		cout << endl;
	}
	*/

	int mindist = INT_MAX;
	//int minpast;
	int sum = 0;
	for (int i = 1; i <= P; i++) {
		sum = 0;
		for (int j = 0; j < N; j++) {
			sum += sp[i][cowAt[j]];
		}
		if (sum < mindist) {
			mindist = sum;
			//minpast = i;
		}
	}

	//cout << mindist << endl;
	fout << mindist << endl;



	
	//endProgram(t1);
	return 0;
}