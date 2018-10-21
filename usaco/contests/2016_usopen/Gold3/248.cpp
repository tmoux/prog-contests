/*
ID: silxikys
PROG: 248
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

ofstream fout("248.out");
ifstream fin("248.in");

const int maxn = 250;
int N;
int nums[maxn];
int dp[maxn][maxn];

int f(int i, int j) {
	if (dp[i][j] != 0) {
		return dp[i][j];
	}
	dp[i][j] = -1;
	if (j == i + 1) {
		return dp[i][j] = nums[i];
	}
	for (int k = i + 1; k < j; k++) {
		if (f(i,k) == f(k,j) && f(i,k) > 0) {
			dp[i][j] = max(dp[i][j],f(i,k) + 1);
		}
	}
	return dp[i][j];
}

int main() 
{
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> nums[i];
	}
	f(0,N);
	int ret = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= N; j++)  {
			ret = max(ret,dp[i][j]);
		}
	}
	cout << ret << '\n';
	fout << ret << '\n';

	return 0;
}