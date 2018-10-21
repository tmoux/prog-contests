/*
ID: silxikys
PROG: gates
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

ofstream fout("gates.out");
ifstream fin("gates.in");

struct Point {
	bool left;
	bool up;
	bool right;
	bool down;
};

const int maxn = 1001;
Point isBlocked[maxn*2][maxn*2];
int component[maxn*2][maxn*2];
bool visited[maxn*2][maxn*2];
int N;
int minx = 1000, miny = 1000;
int maxx = 1000, maxy = 1000;

void setBoundary(int i, int j) {
	//cout << i << ' ' << j << '\n';
	visited[i][j] = true;
	component[i][j] = -1;
	if (i != minx && !isBlocked[i][j].left && !visited[i-1][j]) {
		setBoundary(i-1,j);
	}
	if (i != maxx && !isBlocked[i][j].right && !visited[i+1][j]) {
		setBoundary(i+1,j);
	}
	if (j != miny && !isBlocked[i][j].down && !visited[i][j-1]) {
		setBoundary(i,j-1);
	}
	if (j != maxy && !isBlocked[i][j].up && !visited[i][j+1]) {
		setBoundary(i,j+1);
	}
}

void floodfill(int i, int j, int comp) {
	
	if (i == minx && !isBlocked[i][j].left ||
		i == maxx && !isBlocked[i][j].right ||
		j == miny && !isBlocked[i][j].down ||
		j == maxy && !isBlocked[i][j].up) {
		//unblocked edge, set component to -1
		setBoundary(i,j);
		return;
	}
	
	component[i][j] = comp;
	if (i != minx && !isBlocked[i][j].left && component[i-1][j] == 0) {
		floodfill(i-1,j,comp);
	}
	if (i != maxx && !isBlocked[i][j].right && component[i+1][j] == 0) {
		floodfill(i+1,j,comp);
	}
	if (j != miny && !isBlocked[i][j].down && component[i][j-1] == 0) {
		floodfill(i,j-1,comp);
	}
	if (j != maxy && !isBlocked[i][j].up && component[i][j+1] == 0) {
		floodfill(i,j+1,comp);
	}
	
}

int main() 
{
	//input
	fin >> N;
	int xpos = 1000, ypos = 1000;
	string s; fin >> s;
	for (char c: s) {
		switch (c) {
			case 'N': 
			isBlocked[xpos][ypos].left = true;
			isBlocked[xpos-1][ypos].right = true;
			ypos++;
			break;
			case 'S':
			ypos--;
			isBlocked[xpos][ypos].left = true;
			isBlocked[xpos-1][ypos].right = true;
			break;
			case 'E':
			isBlocked[xpos][ypos].down = true;
			isBlocked[xpos][ypos-1].up = true;
			xpos++;
			break;
			case 'W':
			xpos--;
			isBlocked[xpos][ypos].down = true;
			isBlocked[xpos][ypos-1].up = true;
			break;
		}
		minx = min(minx,xpos);
		maxx = max(maxx,xpos);
		miny = min(miny,ypos);
		maxy = max(maxy,ypos);
	}

	maxx--;
	maxy--;

	cout << minx << ' ' << maxx << '\n' << miny << ' ' << maxy << '\n';
	//floodfill to count how many components there are
	int currComponent = 1;
	
	
	for (int i = minx; i <= maxx; i++) {
		for (int j = miny; j <= maxy; j++) {
			if (component[i][j] == 0) {
				//cout << i << ' ' << j << '\n';
				floodfill(i,j,currComponent);
				if (component[i][j] != -1) {
					currComponent++;
				}
			}
		}
	}
	
	
	//floodfill(minx,miny+2,currComponent);
	//setBoundary(minx,miny+2);
	
	/*
	for (int j = miny; j <= maxy; j++) {
		for (int i = minx; i <= maxx; i++) {
			cout << component[i][j] << ' ';
		} cout << '\n';
	}
	*/

	cout << currComponent - 1 << '\n';
	fout << currComponent - 1 << '\n';






	return 0;
}