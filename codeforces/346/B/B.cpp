#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

int n, m, p;
//n = |s1|, m = |s2|, p = |virus|
const int maxn = 105;
const string INV = "qwer";
string s1, s2, virus;
string dp[maxn][maxn][maxn];

void fillDP() {
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            for (int k = 0; k < maxn; k++) {
                dp[i][j][k] == INV;
            }
        }
    }
}

string f(int i, int j, int k)
{
    if (dp[i][j][k] != INV) return dp[i][j][k];
    if (i == 0 || j == 0) return dp[i][j][k] == "";
    if (s1[i] == s2[j]) {
        
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s2 >> s2 >> virus;
    n = s1.size(); m = s2.size(); p = virus.size();    
    fillDP();
    s1 = ' ' + s1; s2 = ' ' + s2; p = ' ' + p;



    return 0;
}
	

