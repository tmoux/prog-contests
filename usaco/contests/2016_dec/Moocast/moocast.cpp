/*
ID: silxikys
PROG: moocast
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

const int maxn = 200;
int N;
int cows[maxn][3];
vector<int> adjacents[maxn];

void floodfill(int n, int& ncows, int visited[]) {
	ncows++;
	visited[n] = 1;
	for (int adj: adjacents[n]) {
		if (!visited[adj]) {
			floodfill(adj,ncows,visited);
		}
	}
}

int main() {
	ofstream fout("moocast.out");
	ifstream fin("moocast.in");

	//input
	fin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			fin >> cows[i][j];
		}
	}

	//building adjacents matrix
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int d2 = (cows[i][0]-cows[j][0])*(cows[i][0]-cows[j][0])
				    +(cows[i][1]-cows[j][1])*(cows[i][1]-cows[j][1]);
			if (d2 <= cows[i][2]*cows[i][2]) {
				adjacents[i].push_back(j);
			}
		}
	}
	/*	
	for (int i = 0; i < N; i++) {
		cout << i << ": ";
		for (int a: adjacents[i]) {
			cout << a << ' ';
		} cout << '\n';
	}
	*/

	int maxcows = 0;
	for (int i = 0; i < N; i++) {
		int ncows = 0;
		int visited[maxn] = {0};
		floodfill(i,ncows,visited);
		maxcows = max(maxcows, ncows);
	}

	cout << maxcows << '\n';
	fout << maxcows << '\n';

	return 0;
}