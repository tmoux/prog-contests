/*
ID: silxikys
PROG: checklist
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

ofstream fout("checklist.out");
ifstream fin("5.in");

int H, G;
const int maxh = 1001;

int hs[maxh][2];
int gs[maxh][2];
int dp[maxh][maxh][2];

int d2(int p1[2], int p2[2]) {
	return ((p2[0]-p1[0])*(p2[0]-p1[0]))+((p2[1]-p1[1])*(p2[1]-p1[1]));
}

int f(int i, int j, int k) { //k: 0 is hs, 1 is gs
	if (dp[i][j][k] != -1) {
		return dp[i][j][k];
	}
	if (i == 1 && j == 0) {
		return dp[i][j][k] = 0;
	}
	if (i == 1 && j == 1 && k == 1) {
		return dp[i][j][k] = d2(gs[j],hs[i]) + f(i,j-1,0);
	}
	if (i == 2 && j == 1 && k == 0) {
		return dp[i][j][k] = d2(hs[i],gs[j]) + f(i-1,j,1);
	}
	if (i == 2 && j == 1 && k == 1) {
		return dp[i][j][k] = d2(gs[j],hs[i]) + f(i,j-1,0);
	}
	if (i == 1 && k == 1) {
		return dp[i][j][k] = d2(gs[j],gs[j-1]) + f(i,j-1,1);
	}
	if (j == 0 && k == 0) {
		return dp[i][j][k] = d2(hs[i],hs[i-1]) + f(i-1,j,0);
	}
	if (i == 2 && k == 0) {
		return dp[i][j][k] = d2(hs[i],gs[j]) + f(i-1,j,1);
	}
	if (k == 0) {
		return dp[i][j][k] = min(
							     d2(hs[i],hs[i-1]) + f(i-1,j,0),
							     d2(hs[i],gs[j])   + f(i-1,j,1));
	}
	if (k == 1) {
		return dp[i][j][k] = min(
							     d2(gs[j],gs[j-1]) + f(i,j-1,1),
							     d2(gs[j],hs[i])   + f(i,j-1,0));
	}

	
}

int main() 
{
	fin >> H >> G;
	for (int i = 1; i <= H; i++) {
		fin >> hs[i][0] >> hs[i][1];
	}
	for (int i = 1; i <= G; i++) {
		fin >> gs[i][0] >> gs[i][1];
	}
	//initialize dp array
	for (int i = 0; i <= H; i++) {
		for (int j = 0; j <= G; j++) {
			for (int k = 0; k < 2; k++) {
				dp[i][j][k] = -1;
			}
		}
	}

	int ans = f(H, G, 0);
	
	
	
	cout << ans << '\n';
	fout << ans << '\n';


	return 0;
}