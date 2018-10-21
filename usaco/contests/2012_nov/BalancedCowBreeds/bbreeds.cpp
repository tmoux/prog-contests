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

const int maxn = 1005, M = 2012;
int N, excess[maxn], what[maxn], dp[maxn][maxn];
//what = 1 = (, -1 = )

int f(int i, int ex) {
    if (ex < 0 || (excess[i-1] - ex) < 0) return 0;
    if (i > N) {
        if (ex == 0) return 1;
        else return 0;
    }
    if (dp[i][ex] >= 0) return dp[i][ex];
    if (what[i] == 1) {
        return dp[i][ex] = (f(i+1,ex+1) + f(i+1,ex)) % M;
    }
    else {
        return dp[i][ex] = (f(i+1,ex-1) + f(i+1,ex)) % M;
    }
}

int main() 
{
    string s; cin >> s;
    N = s.size();
    for (int i = 1; i <= N; i++) {
        what[i] = (s[i-1] == '(' ? 1 : -1);
        excess[i] = what[i] + excess[i-1];
        if (excess[i] < 0) {
            cout << 0 << '\n';
            fout << 0 << '\n';
            return 0;
        }
    }

    if (excess[N] != 0) {
        cout << 0 << '\n';
        fout << 0 << '\n';
        return 0;
    }
    //calc
    memset(dp,-1,sizeof(dp));
    int ans = f(1,0);
    cout << ans << '\n';
    fout << ans << '\n';
    /*
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            cout << f(i,j) << ' ';
        }
        cout << '\n';
    }

    cout << f(3,2) << '\n';
    */
	return 0;
}

