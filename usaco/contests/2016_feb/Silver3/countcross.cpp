/*
ID: silxikys
PROG: countcross
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

ofstream fout("countcross.out");
ifstream fin("10.in");

struct Point {
	bool left;
	bool right;
	bool up;
	bool down;
};

const int maxn = 101;
Point adjacents[maxn][maxn];
int component[maxn][maxn];

int N, K, R;

void assignComponent(int row, int col, int comp) {
	component[row][col] = comp;
	if (adjacents[row][col].right && !component[row][col+1]) {
		assignComponent(row,col+1,comp);
	}
	if (adjacents[row][col].left && !component[row][col-1]) {
		assignComponent(row,col-1,comp);
	}
	if (adjacents[row][col].up && !component[row-1][col]) {
		assignComponent(row-1,col,comp);
	}
	if (adjacents[row][col].down && !component[row+1][col]) {
		assignComponent(row+1,col,comp);
	}
}

int main() 
{
	//input
	fin >> N >> K >> R;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			adjacents[i][j] = {1,1,1,1};
			if (i == 1) {
				adjacents[i][j].up = 0;
			}
			if (i == N) {
				adjacents[i][j].down = 0;
			}
			if (j == 1) {
				adjacents[i][j].left = 0;
			}
			if (j == N) {
				adjacents[i][j].right = 0;
			}
		}
	}
	
	for (int i = 0; i < R; i++) {
		int r1, c1, r2, c2;
		fin >> r1 >> c1 >> r2 >> c2;
		if (r1 == r2) {
			Point* l;
			Point* r;
			if (c1 < c2) {
				l = &adjacents[r1][c1];
				r = &adjacents[r2][c2];
			}
			else {
				l = &adjacents[r2][c2];
				r = &adjacents[r1][c1];
			}
			l->right = 0;
			r->left = 0;
		}
		
		else if (c1 == c2) {
			Point* u;
			Point* d;
			if (r1 > r2) {
				u = &adjacents[r2][c2];
				d = &adjacents[r1][c1];
			}
			else {
				d = &adjacents[r2][c2];
				u = &adjacents[r1][c1];
			}
			u->down = 0;
			d->up = 0;
		}
	}

	//assign nodes to components
	int curr = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (!component[i][j]) {
				curr++;
				assignComponent(i,j,curr);
			}
			
			//cout << i << ' ' << j << ": " << adjacents[i][j].up << ' ' << adjacents[i][j].right << ' ' << adjacents[i][j].down << ' ' << adjacents[i][j].left << '\n';
		}
	}
	/*
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << component[i][j] << ' ' ;
		} cout << '\n';
	}
	*/
	pair<int,int> cows[maxn*maxn];
	for (int i = 0; i < K; i++) {
		int a, b; fin >> a >> b;
		cows[i] = make_pair(a,b);
	}

	int ans = 0;
	for (int i = 0; i < K; i++) {
		pair<int,int> p1 = cows[i];
		for (int j = i + 1; j < K; j++) {
			pair<int,int> p2 = cows[j];
			if (component[p1.first][p1.second] != component[p2.first][p2.second]) {
				ans++;
			}
		}
	}

	cout << ans << '\n';
	fout << ans << '\n';
	

	return 0;
}