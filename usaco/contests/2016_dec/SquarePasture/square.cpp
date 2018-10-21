/*
ID: silxikys
PROG: square
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



int main() {
	ofstream fout("square.out");
	ifstream fin("square.in");

	//input
	int r[2][4];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			fin >> r[i][j];
		}
	}

	int maxx = max(r[0][2],r[1][2]);
	int minx = min(r[0][0],r[1][0]);
	int maxy = max(r[0][3],r[1][3]);
	int miny = min(r[0][1],r[1][1]);


	int side = max(maxx-minx,maxy-miny);

	cout << (side*side) << '\n';
	fout << (side*side) << '\n';

	return 0;
}