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

struct di {
	int maxrow;
	int maxcol;

	inline int area() {
		return maxrow * maxcol;
	}
};

int R, C, P;
const int maxx = 3005;
bool exes[maxx][maxx];
di grid[2][maxx];

int main() {
	t1 = gettime();
	ofstream fout("rectbarn.out");
	ifstream fin("rectbarn.in");

	fin >> R >> C >> P;
	for (int i = 0; i < P; i++) {
		int a, b; fin >> a >> b;
		exes[a][b] = 1;
	}
	/*
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << exes[i][j];
		} cout << '\n'; 
	}
	*/
	//fill in grid
	int maxarea = 0;

	for (int j = 1; j <= C; j++) {
		grid[0][j] = {0,0};
	}
	grid[1][0] = {0,0};

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			int row, col;
			di r1 = grid[0][j];
			di r2 = grid[1][j-1];
			if (exes[i][j]) {
				row = 0;
				col = 0;
			}
			else if (r1.maxrow == 0 && r1.maxcol == 0 && r2.maxrow == 0 && r2.maxcol == 0) {
				row = 1;
				col = 1;
			}
			else {

				di s1 = {r1.maxrow+1,min(r1.maxcol,r2.maxcol+1)};
				di s2 = {min(r2.maxrow,r1.maxrow+1),r2.maxcol+1};
				if (s1.area() > s2.area()) {
					row = s1.maxrow;
					col = s1.maxcol;
				}
				else {
					row = s2.maxrow;
					col = s2.maxcol;
				}
			}
			grid[1][j] = {row,col};
			grid[0][j] = {row,col};
			
			if (row*col > maxarea) {
				//cout << i << ' ' << j << ' ' << row*col << ' ' << row << ' ' << col << '\n';
				maxarea = row*col;
			}


		}
		//cout << maxarea << '\n';

	}
	
	cout << maxarea << '\n';

	fout << maxarea << '\n';
	

	
	endProgram(t1);
	return 0;
}