/*
ID: silxikys
PROG: snail
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

int N, B;
const int maxn = 121;
int grid[maxn][maxn];
int newrow[4] = {-1,0,1,0};
int newcol[4] = {0,1,0,-1};
int maxcount = 0;
//0 is up, 1 is right, 2 is down, 3 is left
int charToInt(char c) {
	return (int(c) - 65);
}

void printGrid() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << grid[i][j];
		} cout << '\n';
	}
}

inline bool validSquare(int row, int col) {
	return (row >= 0 && row < N && col >= 0 && col < N && !grid[row][col]);
}



void depthsearch(int row, int col, int dir, int count=1) {
	int nextrow = row + newrow[dir];
	int nextcol = col + newcol[dir];

	if (grid[nextrow][nextcol] == 1) {//place snail already been
		maxcount = max(maxcount,count);
	}
	else if (validSquare(nextrow,nextcol)) {
		grid[row][col] = 1;
		depthsearch(nextrow,nextcol,dir,count+1);
	}
	else {
		//try to go to left or right
		bool isEnd = true;
		int nextdir = (dir + 1) % 4;
		nextrow = row + newrow[nextdir];
		nextcol = col + newcol[nextdir];
		if (validSquare(nextrow,nextcol)) {
			grid[row][col] = 1;
			depthsearch(nextrow,nextcol,nextdir,count+1);
			isEnd = false;
		}
		nextdir = (dir - 1 + 4) % 4;
		nextrow = row + newrow[nextdir];
		nextcol = col + newcol[nextdir];
		if (validSquare(nextrow,nextcol)) {
			grid[row][col] = 1;
			depthsearch(nextrow,nextcol,nextdir,count+1);
			isEnd = false;
		}

		if (isEnd) {
			//cout << count << endl;
			//printGrid();
			maxcount = max(maxcount, count);

		}
	}
	grid[row][col] = 0;
	return;
} 

int main() {
	t1 = gettime();
	ofstream fout("snail.out");
	ifstream fin("snail.in");

	//input
	fin >> N >> B;
	/*
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			grid[i][j] = 0;
		}
	}
	*/
	string barrier;
	for (int i = 0; i < B; i++) {
		fin >> barrier;
		int col = charToInt(barrier[0]);
		int row = atoi(barrier.substr(1,barrier.length()-1).c_str());
		grid[row-1][col] = 2;
	}

	//printGrid();
	//do calculations
	depthsearch(0,0,2);
	depthsearch(0,0,1);

	//printGrid();
	//depthsearch(0,0,2);

	cout << maxcount << endl;
	fout << maxcount << endl;
	endProgram(t1);
	return 0;
}