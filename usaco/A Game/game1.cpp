/*
ID: silxikys
PROG: game1
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

const int maxn = 101;
int dp[maxn][maxn];
int board[maxn];
int N;

int maxscore(int i, int j) {
	if (dp[i][j] != 0) {
		return dp[i][j];
	}
	if (i == j) {
		return dp[i][j] = board[i];
	}
	if (i + 1 == j) {
		return dp[i][j] = max(board[i],board[j]);
	}
	return dp[i][j] = max(board[i]+min(maxscore(i+2,j),maxscore(i+1,j-1)),
						  board[j]+min(maxscore(i,j-2),maxscore(i+1,j-1)));
}

int main() {
	t1 = gettime();
	ofstream fout("game1.out");
	ifstream fin("game1.in");

	//input
	int total = 0;
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> board[i];
		total += board[i];
	}
	int ans = maxscore(0,N-1);
	int complement = total - ans;
	fout << ans << " " << complement << endl;
	endProgram(t1);
	return 0;
}