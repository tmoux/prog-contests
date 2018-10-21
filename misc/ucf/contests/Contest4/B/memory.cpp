#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;
typedef long long ll;

const int maxn = 405;
const double INF = 999999999;
int n, m;
double dp[maxn][maxn][maxn];

double f(int t, int c, int k) {
    if (c <= 0) return 0.0;
    if (t == m) return 0.0;
    //k = max(k,0);
    //cout << t << ' ' << c << ' ' << k << '\n';
    if (dp[b][t][c][k] != INF) return dp[b][t][c][k];
    cout << t << ' ' << c << ' ' << k << ' ' << b << '\n';
    int add = (t % 2 ? -1 : 1);
    if (k*2 > c) {
        return dp[b][t][c][k] = add + f(0,c-2,k-2,!b);
    }
    if (k == 0) {
        return dp[b][t][c][k] = 2.0/(double)(c)*(add + f(0,c-2,k,!b)) + (1.0-2.0/(double)(c)*(f(t+1,c,k+2,!b)));
    }
    return dp[b][t][c][k] = 
        (double)k/(c-k)*(add + f(0,c-2,k-1,!b)) +
        (double)(c-2*k)/((c-k)*(c-k-1))*(
        (1.0)*(add+f(0,c-2,k,!b))+
        (double)(c-2*k-2)*(f(t+1,c,k+2,!b))+
        (double)(k)*(-add + f(0,c-2,k,b)));
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < maxn; j++) {
            for (int k = 0; k < maxn; k++) {
                for (int l = 0; l < maxn; l++) {
                    dp[i][j][k][l] = INF;
                }
            }
        }
    }
    double ans = f(0,n,0,0);
    cout << fixed << setprecision(4) << ans << '\n';

    return 0;
}
	

