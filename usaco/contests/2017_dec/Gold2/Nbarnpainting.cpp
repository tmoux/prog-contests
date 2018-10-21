/*
ID: silxikys
PROG: barnpainting
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

ofstream fout("barnpainting.out");
ifstream fin("barnpainting.in");
const int maxn = 100005;
const int MOD = 1000000007;
long dp[maxn][3];
int colored[maxn];
vector<int> adjacents[maxn];
int N, K;

long f(int v, int c, int rV, int rC) {
	//cout << v << ' ' << c << ' ' << rV << ' ' << rC << '\n';
	if ((colored[v] > 0 && colored[v] != c) || (c == rC)) {
		return 0;
	}
	if (dp[v][c] > 0) {
		return dp[v][c];
	}
	dp[v][c] = 1;
	for (int u: adjacents[v]) {
		if (u == rV) {continue;}
		long count = 0;
		for (int cprime = 1; cprime <= 3; cprime++) {
			count += f(u,cprime,v,c);
			count %= MOD;
		}
		dp[v][c] *= count;
		dp[v][c] %= MOD;
		//cout << v << ' ' << u << ' ' << dp[v][c] << '\n';
	}
	return dp[v][c];
}

int main() 
{
	fin >> N >> K;
	for (long i = 1; i < N; i++) {
		long x, y; fin >> x >> y;
		adjacents[x].push_back(y);
		adjacents[y].push_back(x);
	}
	for (long i = 0; i < K; i++) {
		long b, c; fin >> b >> c;
		colored[b] = c;
	}
	long ans = (f(1,2,0,0) + f(1,3,0,0) + f(1,1,0,0)) % MOD;
	cout << ans << '\n';
	fout << ans << '\n'; 

	return 0;
}