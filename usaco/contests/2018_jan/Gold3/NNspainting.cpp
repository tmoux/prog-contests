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

const int maxn = 1000001;
const int MOD = 1000000007;
int N, M, K;

long long dp[maxn];

long long power(int m, int n)
{
	long long ret = 1;
	for (int i = 0; i < n; i++) {
		ret = (ret * m) % MOD;
	}
	return ret;
}

int main() 
{
	fin >> N >> M >> K;
	long long total = power(M,N);
	dp[0] = 0;
	for (int i = 1; i <= N; i++) {
		if (i < K) {
			dp[i] = (M*dp[i-1] + M) % MOD;
		}
		else {
			dp[i] = (M*(dp[i-1])-(M-1)*(dp[i-K])) % MOD;
		}
		
	}
	//cout << dp[N] << '\n';
	int ans = (total - (dp[N] - dp[N-1]) + MOD) % MOD;
	cout << ans << '\n';
	fout << ans << '\n';


	return 0;
}