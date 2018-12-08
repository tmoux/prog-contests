/*
ID: silxikys
PROG: hopscotch
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;

ofstream fout("hopscotch.out");
ifstream fin("hopscotch.in");

const int maxc = 102;
const int MOD = 1000000007;
int grid[maxc][maxc];
int R, C, K;
long dp[maxc][maxc];

long f(int i, int j) {
	if (dp[i][j] != -1) {
		return dp[i][j];
	}
	if (i == R - 1 && j == C - 1) {
		return dp[i][j] = 1;
	}
	dp[i][j] = 0;
	for (int ii = i + 1; ii < R; ii++) {
		for (int jj = j + 1; jj < C; jj++) {
			if (grid[ii][jj] != grid[i][j]) {
				dp[i][j] += f(ii,jj);
				dp[i][j] %= MOD;
			}
		}
	}
	return dp[i][j];
}

int main() 
{
	memset(dp,-1,sizeof(dp));
	fin >> R >> C >> K;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			fin >> grid[i][j];
		}
	}

	long ans = f(0,0);
	cout << ans << '\n';
	fout << ans << '\n';


	return 0;
}