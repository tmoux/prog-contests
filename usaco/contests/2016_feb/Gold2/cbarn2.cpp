/*
ID: silxikys
PROG: cbarn2
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

ofstream fout("cbarn2.out");
ifstream fin("cbarn2.in");

const int maxn = 101;
const int maxk = 7;
const int INF = 999999999;
int N, K;
int numcows[2*maxn];
int dp[maxn][maxn][maxn][maxk+1];

int f(int i, int n, int d, int k) 
{
	if (dp[i][n][d][k] != -1) {
		return dp[i][n][d][k];
	}
	if (n >= i + N) {
		return dp[i][n][d][k] = 0;
	}
	if (k == 0) {
		dp[i][n][d][k] = numcows[n]*d + f(i,n+1,d+1,k);
	}
	else {
		dp[i][n][d][k] = min(numcows[n]*d + f(i,n+1,d+1,k), f(i,n+1,1,k-1));
	}
	if (dp[i][n][d][k] < 0) dp[i][n][d][k] = INF;
	return dp[i][n][d][k];
}

int main() 
{
	memset(dp,-1,sizeof(dp));
	fin >> N >> K;
	for (int i = 0; i < N; i++) {
		fin >> numcows[i];
		numcows[i+N] = numcows[i];
	}
	int minans = 2000000000;
	for (int i = 0; i < N; i++) {
		//cout << i << ' ' << f(i,i,0,K-1) << '\n';
		minans = min(minans,f(i,i,0,K-1));
	}

	cout << minans << '\n';
	fout << minans << '\n';


	return 0;
}