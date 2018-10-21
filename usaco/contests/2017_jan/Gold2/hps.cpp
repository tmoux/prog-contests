/*
ID: silxikys
PROG: hps
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

ofstream fout("hps.out");
ifstream fin("hps.in");

const int maxn = 100005, maxk = 21;
int dp[maxn][maxk][3];

int N, K;
int gest[maxn];

int isWin(int n, int m) {
	if (gest[n] == 0 && m == 1 ||
		gest[n] == 1 && m == 2 ||
		gest[n] == 2 && m == 0) {
		return 1;
	}
	return 0;
}

int winSwitch(int n) {
	return (gest[n] + 1) % 3;
}

int f(int n, int k, int m) {
	if (dp[n][k][m] != -1) {
		return dp[n][k][m];
	}
	if (n == N+1) {
		return dp[n][k][m] = 0;
	}
	if (k == 0) {
		return dp[n][k][m] = isWin(n,m) + f(n+1,k,m);
	}
	return dp[n][k][m] = max(isWin(n,m) + f(n+1,k,m),
				                      1 + f(n+1,k-1,winSwitch(n)));

}

map<char,int> mapping = {{'H',0},
						 {'P',1},
						 {'S',2}};

int main() 
{
	fin >> N >> K;
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= K; j++) {
			for (int k = 0; k < 3; k++) {
				dp[i][j][k] = -1;
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		char c; fin >> c;
		gest[i] = mapping[c];
	}

	int ans = max(f(1,K,0),max(f(1,K,1),f(1,K,2)));

	cout << ans << '\n';
	fout << ans << '\n';


	return 0;
}