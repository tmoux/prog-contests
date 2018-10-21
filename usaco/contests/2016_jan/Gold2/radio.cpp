/*
ID: silxikys
PROG: radio
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

ofstream fout("radio.out");
ifstream fin("radio.in");

int N, M;
const int maxn = 1001;
map<char,int> dx = {{'N',0},{'W',-1},{'S',0},{'E',1}};
map<char,int> dy = {{'N',1},{'W',0},{'S',-1},{'E',0}};
int dp[maxn][maxn];
pair<int,int> farmer[maxn], cow[maxn];

int energy(const pair<int,int>& p1, const pair<int,int>& p2) {
	return (p1.first-p2.first)*(p1.first-p2.first) + (p1.second-p2.second)*(p1.second-p2.second);
}

int f(int n, int m) {
	if (dp[n][m] != -1) {
		return dp[n][m];
	}
	if (n == 0 && m == 0) {
		return dp[n][m] = 0;
	}
	int addEnergy = energy(farmer[n],cow[m]);
	if (n == 0) {
		return dp[n][m] = addEnergy + f(n,m-1);
	}
	if (m == 0) {
		return dp[n][m] = addEnergy + f(n-1,m);
	}
	return dp[n][m] = addEnergy + min(f(n,m-1),min(f(n-1,m),f(n-1,m-1)));
}

int main() 
{
	fin >> N >> M;
	int initx, inity;
	fin >> initx >> inity;
	farmer[0] = make_pair(initx,inity);
	fin >> initx >> inity;
	cow[0] = make_pair(initx,inity);
	for (int i = 1; i <= N; i++) {
		char c; fin >> c;
		farmer[i] = make_pair(farmer[i-1].first + dx[c], farmer[i-1].second+dy[c]);
	}
	for (int i = 1; i <= M; i++) {
		char c; fin >> c;
		cow[i] = make_pair(cow[i-1].first + dx[c], cow[i-1].second+dy[c]);
	}

	//initialize dp
	memset(dp,-1,sizeof(dp));
	int ans = f(N,M);
	cout << ans << '\n';
	fout << ans << '\n';
	/*
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			cout << dp[i][j] << ' ';
		} cout << '\n';
	}
	*/

	return 0;
}