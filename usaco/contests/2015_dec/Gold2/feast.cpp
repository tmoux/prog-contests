/*
ID: silxikys
PROG: feast
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

ofstream fout("feast.out");
ifstream fin("feast.in");

const int maxt = 5000001;
int dp[maxt][2]; //0 is can drink, 1 is already drank
int T, A, B;

int f(int t, int canDrink) {
	if (dp[t][canDrink] != 0) {
		return dp[t][canDrink];
	}
	int ret = t;
	if (t + A <= T) {
		ret = max(ret,f(t+A,canDrink));
	}
	if (t + B <= T) {
		ret = max(ret,f(t+B,canDrink));
	}
	if (canDrink == 0) {
		ret = max(ret,f(t/2,1));
	}
	return dp[t][canDrink] = ret;
}

int main() 
{
	fin >> T >> A >> B;
	int ans = f(0,0);
	cout << ans << '\n';
	fout << ans << '\n';
	return 0;
}