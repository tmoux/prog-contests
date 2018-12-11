/*
ID: silxikys
PROG: twofive
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <deque>
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
const int SIZE = 3;

struct Grid
{
	int grid[SIZE][SIZE];
	Grid() {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				grid[i][j] = i*SIZE + j;
			}
		}
	}
	Grid(int init[SIZE][SIZE]) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				grid[i][j] = init[i][j];
			}
		}
	}
	Grid(const Grid& g) {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				grid[i][j] = g.grid[i][j];
			}
		}
	}
	void pprint() {
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				cout << grid[i][j] << ' ';
			} cout << '\n';
		}
		cout << '\n';
	}
	bool operator==(const Grid& rhs)
	{
    	for (int i = 0; i < SIZE; i++) {
    		for (int j = 0; j < SIZE; j++) {
    			if (grid[i][j] != rhs.grid[i][j]) {
    				return false;
    			}
    		}
    	}
    	return true;
	}
	bool operator<(const Grid& a) const //for sorting
    {
        for (int i = 0; i < SIZE; i++) {
        	for (int j = 0; j < SIZE; j++) {
        		if (grid[i][j] != a.grid[i][j]) {
        			return (grid[i][j] < a.grid[i][j]);
        		}
        	}
        }
    }
	bool isValid(int r1, int c1, int r2, int c2) {
		if (r1 != 0 && grid[r1-1][c1] > grid[r1][c1]) {return false;}
		if (r2 != 0 && grid[r2-1][c2] > grid[r2][c2]) {return false;}
		if (r1 != SIZE - 1 && grid[r1+1][c1] < grid[r1][c1]) {return false;}
		if (r2 != SIZE - 1 && grid[r2+1][c2] < grid[r2][c2]) {return false;}
		if (c1 != 0 && grid[r1][c1-1] > grid[r1][c1]) {return false;}
		if (c2 != 0 && grid[r2][c2-1] > grid[r2][c2]) {return false;}
		if (c1 != SIZE - 1 && grid[r1][c1+1] < grid[r1][c1]) {return false;}
		if (c2 != SIZE - 1 && grid[r2][c2+1] < grid[r2][c2]) {return false;}
		return true;
	}

	vector<Grid> makeGrids() {
		vector<Grid> ret;
		for (int row = SIZE - 1; row >= 0; row--) {
			for (int col = SIZE - 1; col >= 0; col--) {
				//for each number in the row
				for (int i = SIZE - 1; i > row; i--) {
					for (int j = col - 1; j >= 0; j--) {
						//try to switch (row,col) with (i,j)
						if (grid[row][col] < grid[i][j]) {
							//create a new grid
							Grid newGrid(*this);
							newGrid.grid[i][j] = grid[row][col];
							newGrid.grid[row][col] = grid[i][j];
							if (newGrid.isValid(row, col, i, j)) {
								//cout << row << ' ' << col << ' ' << i << ' ' << j << '\n' << newGrid.isValid(row,col, i, j) << '\n';
								//newGrid.pprint();
								ret.push_back(newGrid);
							}
						}
					}
				}
			}
		}
		return ret;
	}
};


int main() {
	t1 = gettime();
	ofstream fout("twofive.out");
	ifstream fin("twofive.in");

	
	
	Grid orig;
	deque<Grid> deq = {orig};
	vector<Grid> allgrids = {orig};
	while (deq.size() != 0) {
		vector<Grid> toAdd = deq.front().makeGrids();
		for (Grid g: toAdd) {

			bool alreadyfound = false;
			
			for (Grid r: allgrids) {
				if (r == g) {
					alreadyfound = true;
					break;
				}
			}
			
			if (!alreadyfound) {
				deq.push_back(g);	
				allgrids.push_back(g);
			}			
		}

		deq.pop_front();
		
		
	}


	//sort(allgrids.begin(),allgrids.end());
	cout << allgrids.size() << '\n';
	
	for (Grid g: allgrids) {
		g.pprint();
	}
	
	
	
	endProgram(t1);
	return 0;
}