/*
ID: silxikys
PROG: vans
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

const int maxn = 1001;
const int maxr = 4;
int curgrid[maxr][maxn];
int N, cursize, numways, targetsize;

void dfs(int row1, int col1, int row2, int col2) {
	//cout << row << ' ' << col << '\n';
	bool foundAny1 = false, foundAny2 = false;
	curgrid[row1][col1] = 1;
	cursize++;
	curgrid[row2][col2] = 1;
	cursize++;
	vector<pair<int,int>> oneposs, twoposs;
	if (col1 != 0 && !curgrid[row1][col1-1]) {
		oneposs.push_back(make_pair(0,-1));
	}
	if (col1 != N - 1 && !curgrid[row1][col1+1]) {
		oneposs.push_back(make_pair(0,1));
	}
	if (row1 != 0 && !curgrid[row1-1][col1]) {
		oneposs.push_back(make_pair(-1,0));
	}
	if (row1 != maxr - 1 && !curgrid[row1+1][col1]) {
		oneposs.push_back(make_pair(1,0));
	}


	if (col2 != 0 && !curgrid[row2][col2-1]) {
		twoposs.push_back(make_pair(0,-1));
	}
	if (col2 != N - 1 && !curgrid[row2][col2+1]) {
		twoposs.push_back(make_pair(0,1));
	}
	if (row2 != 0 && !curgrid[row2-1][col2]) {
		twoposs.push_back(make_pair(-1,0));
	}
	if (row2 != maxr - 1 && !curgrid[row2+1][col2]) {
		twoposs.push_back(make_pair(1,0));
	}

	for (pair<int,int> p: oneposs) {
		for (pair<int,int> q: twoposs) {
			dfs(row1+p.first,col1+p.second,row2+q.first,col2+q.second);
		}
	}
	if (oneposs.size() == 0 && twoposs.size() == 0 && cursize == targetsize) {
		if (abs(row1-row2) + abs(col1-col2) == 1) {
			numways++;
		}
	}
	cursize--;
	curgrid[row1][col1] = 0;
	cursize--;
	curgrid[row2][col2] = 0;
}

int main() {
	t1 = gettime();
	ofstream fout("vans.out");
	ifstream fin("vans.in");

	fin >> N;
	targetsize = maxr * N;
	dfs(0,0,0,1);

	numways *= 2;
	cout << numways << '\n';
	fout << numways << '\n';


	
	endProgram(t1);
	return 0;
}