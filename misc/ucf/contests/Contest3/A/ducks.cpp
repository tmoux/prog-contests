#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 2005;
int dp[maxn][maxn];
int n, k;
bool A[maxn];

int f(int i, int j) {
    if (dp[i][j] >= 0) return dp[i][j];
    
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    string s; cin >> s;
    memset(dp,-1,sizeof(dp));
    for (int i = 0; i < s.size(); i++) {
        A[i] = s[i] == 'D';
    }

    int ans = f(0,0);


    return 0;
}
	

