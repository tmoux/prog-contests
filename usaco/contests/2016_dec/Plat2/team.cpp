#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MOD = 1000000009;
const int maxn = 1001;
const int maxk = 11;
long dp[maxn][maxn][maxk];
int fj[maxn], fp[maxn];

long f(int i, int j, int k) {
	if (dp[i][j][k] != -1) {
		return dp[i][j][k];
	}
	
}

int main()
{
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	freopen("team.in","r",stdin);
	ofstream fout("team.out");
	memset(dp,-1,sizeof(dp));
	
	
	
	
	return 0;
}

