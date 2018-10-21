/*
ID: silxikys
PROG: program
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

ofstream fout("bbreeds.out");
ifstream fin("bbreeds.in");

const int maxn = 1005;
const int M = 2012;
int paren[1005], numunpaired[maxn]; 
int n;

int dp[maxn][maxn];

int f(int i, int unB) {
    if (dp[i][unB] >= 0) return dp[i][unB];
    cout << i << ' ' << unB << '\n';
    if (i == n) {
        if (unB == 0) return dp[i][unB] = 1;
        return 1;
    }
    if (paren[i] == 1) {
        return dp[i][unB] = (f(i+1,unB+1) + f(i+1,unB)) % M;
    }
    else {
        dp[i][unB] = 0;
        int unR = numunpaired[i] - unB;
        if (unB > 0) dp[i][unB] = (dp[i][unB] + f(i+1,unB-1)) % M;
        if (unR > 0) dp[i][unB] = (dp[i][unB] + f(i+1,unB)) % M;
        return dp[i][unB];
    }
}

int main() 
{
    string s; fin >> s;
    n = s.size();
    memset(dp,-1,sizeof(dp));
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            paren[i] = 1;
        }
        else {
            paren[i] = -1;
        }
        if (i == 0) numunpaired[i] = paren[i];
        else numunpaired[i] = numunpaired[i-1] + paren[i];

        if (numunpaired[i] < 0) {
            //invalid
            cout << 0 << '\n';
            return 0;
        }
    }

    int ans = f(0,0);
    cout << ans << '\n';
	return 0;
}

