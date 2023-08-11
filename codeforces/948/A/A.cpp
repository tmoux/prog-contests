#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

char grid[505][505];
int R, C; 

void placeSquare(int i,int j) {
	if (grid[i][j] == '.') {
		grid[i][j] = 'D';
	}
}

void tryplace(int i, int j) {
	if (i != 0) {
		placeSquare(i-1,j);
		if (j != 0) placeSquare(i-1,j-1);
		if (j != C - 1) placeSquare(i+1,j-1);
	}
	if (i != R - 1) {
		placeSquare(i+1,j);
		if (j != 0) placeSquare(i+1,j-1);
		if (j != C - 1) placeSquare(i+1,j-1);
	}
	if (j != 0) {
		placeSquare(i,j-1);
	}
	if (j != C - 1) {
		placeSquare(i,j+1);
	}
}

bool checkSquare(int i, int j) {
	if (i != 0 && grid[i-1][j] == 'W') {
		return false;
	}
	if (i != R-1 && grid[i+1][j] == 'W') {
		return false;
		
	}
	if (j != 0 && grid[i][j-1] == 'W') {
		return false;
	}
	if (j != C - 1 && grid[i][j+1] == 'W') {
		return false;
	}
	return true;
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	//freopen("input.in","r",stdin);
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		string s; cin >> s;
		for (int j = 0; j < C; j++) {
			grid[i][j] = s[j];
		}
	}
	bool canDo = true;
	for (int i = 0; i < R && canDo; i++) {
		for (int j = 0; j < C; j++) {
			if (grid[i][j] == 'S') {
				if (!checkSquare(i,j)) {
					canDo = false; 
					break;
				}
				tryplace(i,j);
			}
		}
	}
	
	if (canDo) {
		cout << "Yes\n";
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cout << grid[i][j];
			}
			cout << '\n';
		}
	}
	else {
		cout << "No\n";
	}
	
	
	return 0;
}

