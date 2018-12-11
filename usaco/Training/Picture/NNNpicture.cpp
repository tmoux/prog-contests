/*
ID: silxikys
PROG: picture
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
#include <cstring>
using namespace std;
using namespace std::chrono;

#define gettime() (high_resolution_clock::now())
#define endProgram(t1) \
	fin.close(); \
 	fout.close(); \
 	cout << endl << "Execution time: " << duration_cast<nanoseconds>(gettime()-t1).count()/1000000000.0 << " seconds" << endl;
high_resolution_clock::time_point t1;

const int maxn = 5001;

struct line {
	int x1, x2;
	int y;
	int flag;
};

int N;
line verts[maxn*2];
line horiz[maxn*2];

int peri(line* li) {
	int grid[2][20005];
	int l, x, y, g;
	int p = 0;

	memset(grid, 0, sizeof(int)*2*20005);

	l = 0;
	while (l < N) {
		y = li[l].y;
		memcpy(grid[0],grid[1],sizeof(int)*20005);

		while (li[l].y == y) {
			for (x=li[l].x1+10000; x < li[l].x2+10000; x++) {
				grid[1][x] += li[l].flag;
			}
			l++;
			if (l == N) {
				break;
			}
		}

		for (x = 0; x <= 20000; x++) {
			if ((grid[0][x] == 0) && (grid[1][x] > 0)) p++;
			if ((grid[0][x] > 0) && (grid[1][x] == 0)) p++;
		}
	}
	return p;
}

int main() {
	t1 = gettime();
	ofstream fout("picture.out");
	ifstream fin("picture.in");

	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		fin >> x1 >> y1 >> x2 >> y2;

		horiz[i*2] = {x1, x2, y1, 1};
		horiz[i*2+1] = {x1, x2, y2, -1};

		verts[i*2] = {y1, y2, x1, 1};
		verts[i*2+1] = {y1, y2, x2, -1};
	}

	N *= 2;

	sort(horiz, horiz+N, []( const line& lhs, const line& rhs )
	{return lhs.y < rhs.y;});
	sort(verts, verts+N, []( const line& lhs, const line& rhs )
	{return lhs.y < rhs.y;});

	/*
	for (int i = 0; i < N; i++) {
		line l = horiz[i];
		cout << l.y << " " << l.x1 << " " << l.x2 << " " << " " << l.flag << '\n'; 
	}
	*/
	int ans = peri(horiz) + peri(verts);
	cout << ans << endl;
	fout << ans << endl;
	

	
	endProgram(t1);
	return 0;
}