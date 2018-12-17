/*
ID: silxikys
PROG: nocross
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

ofstream fout("nocross.out");
ifstream fin("nocross.in");

const int maxn = 1001;
const int dist = 4;
int N;
int side1[maxn], side2[maxn];
int dp[maxn][maxn]; //one is the current field, that can use starting with '2' side2
int f(int i, int j) 
{
	if (dp[i][j] != -1) {
		return dp[i][j];
	}
	if (i == N || j == N) {
		return dp[i][j] = 0;
	}
	int newj = j;
	while (abs(side1[i] - side2[newj]) > 4) {
		newj++;
		if (newj == N) {
			return dp[i][j] = f(i+1,j);
		}
	}
	return dp[i][j] = max(1 + f(i+1,newj+1), f(i+1,j));
}

int main() 
{
	fin >> N;
	memset(dp,-1,sizeof(dp));
	for (int i = 0; i < N; i++) {
		fin >> side1[i];
	}
	for (int i = 0; i < N; i++) {
		fin >> side2[i];
	}
	int ans = f(0,0);
	cout << ans << '\n';
	fout << ans << '\n';	
	return 0;
}
