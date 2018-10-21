/*
ID: silxikys
PROG: rectbarn
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

struct tri
{
	int height;
	int left;
	int right;

	int area() {
		return height*(left+right+1);
	}
};

const int maxx = 3005;
const int infinity = 99999;
int R, C, P;
vector<int> exes[maxx];
bool isEx[maxx][maxx];
tri f[2][maxx];

//findleft and findright finds the number of spaces between
//the (i,j) and the closest x on the left/right (not inclusive)
int findLeft(int i, int j) {
	int ret = j - 1;
	for (int c: exes[i]) {
		if (c > j) {
			break;
		}
		ret = j - c - 1;
	}
	return ret;
}
int findRight(int i, int j) {
	int ret = C - j;
	for (int a = exes[i].size() - 1; a >= 0; a--) {
		int c = exes[i][a];
		if (c < j) {
			break;
		}
		ret = c - j - 1;
	}
	return ret;
}

int main() {
	t1 = gettime();
	ofstream fout("rectbarn.out");
	ifstream fin("rectbarn.in");

	fin >> R >> C >> P;
	for (int i = 0; i < P; i++) {
		int a, b; fin >> a >> b;
		isEx[a][b] = 1;
		exes[a].push_back(b);
	}
	
	//sort exes
	for (int i = 1; i <= R; i++) {
		sort(exes[i].begin(),exes[i].end());
	}

	
	//fill in grid
	int maxarea = 0;
	for (int i = 1; i <= C; i++) {
		f[0][i] = {0,infinity,infinity};
	}
	//for each row and column, find largest rectangle 
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (isEx[i][j]) {
				f[1][j] = {0,infinity,infinity};
			}
			else {
				int height = f[0][j].height + 1;
				int left = min(f[0][j].left,findLeft(i,j));
				int right = min(f[0][j].right,findRight(i,j));
				f[1][j] = {height,left,right};
			}
			maxarea = max(maxarea,f[1][j].area());
			f[0][j] = f[1][j];
		}
	}
	cout << maxarea << '\n';
	fout << maxarea << '\n';	
	endProgram(t1);
	return 0;
}
