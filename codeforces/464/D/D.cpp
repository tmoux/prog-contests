#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <iomanip>
using namespace std;
typedef long long ll;

const int maxn = 100005;
const int maxj = 1000;
int n, k;
double dp[2][maxj];

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    fill(dp[0],dp[0]+maxj,0.0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < maxj-1; j++) {
            double kk = (double)k;
            double jj = (double)j;
            dp[1][j] = 1.0/(kk*(jj+1.0))*(jj*(jj+3.0)/2.0 + jj * dp[0][j] + dp[0][j+1]) + (1.0-1.0/kk)*dp[0][j];
        }
        for (int j = 1; j < maxj-1; j++) {
            dp[0][j] = dp[1][j];
        }
    }
    cout << fixed << setprecision(10) << k*dp[1][1] << '\n';


    return 0;
}
	

