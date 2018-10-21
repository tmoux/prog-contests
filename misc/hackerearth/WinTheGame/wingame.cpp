#include <iostream>
#include <iomanip>
const int maxn = 1001;
double dp[maxn][maxn];

double f(int r, int g) {
    if (g < 0) return 0;
    if (dp[r][g] != -1) return dp[r][g];
    if (r == 0 || g == 0) return dp[r][g] = 1;
    return (double)r/(r+g) + (double)g/(r+g)*(double)(g-1)/(r+g-1)*f(r,g-2);
}
using namespace std;

int main() {
	freopen("input.in","r",stdin);
	for (int i = 0; i < maxn; i++) {
	    for (int j = 0; j < maxn; j++) {
	        dp[i][j] = -1;
	    }
	}
	int t; cin >> t;
	while (t--) {
	    int r, g; cin >> r >> g;
	    cout << fixed << setprecision(6) << f(r,g) << '\n';
	}
}

