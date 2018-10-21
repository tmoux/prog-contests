/*
ID: silxikys
PROG: spainting
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

ofstream fout("spainting.out");
ifstream fin("spainting.in");

const int MOD = 1000000007;
const int maxn = 2000;
const int NANA = 2000000000;
long long dp[maxn][maxn][2];
int N, M, K;

long long f(int n, int c, int h) {
	//cout << n << ' ' << c << ' ' << h << '\n';
	if (dp[n][c][h] != NANA) {
		return dp[n][c][h];
	}

	if (n == N && h == 1) {
		return dp[n][c][h] = 1;
	}
	if (n == N && h == 0) {
		return dp[n][c][h] = 0;
	}
	if (h == 1) {
		return dp[n][c][h] = (M*f(n+1,c,h)) % MOD;
	}
	if (c == K - 1) {
		return dp[n][c][h] = (f(n+1,c+1,1) + (M-1)*f(n+1,1,h)) % MOD;
	}
	else {
		return dp[n][c][h] = (f(n+1,c+1,h) + (M-1)*f(n+1,1,h)) % MOD;
	}
}

int main() 
{
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < maxn; j++) {
			for (int k = 0; k < 2; k++) {
				dp[i][j][k] = NANA;
			}
		}
	}
	fin >> N >> M >> K;
	long long ans = f(0,0,0);
	cout << ans << '\n';
	fout << ans << '\n';



	return 0;
}