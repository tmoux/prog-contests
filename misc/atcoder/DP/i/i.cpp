#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3005;
int N;
double p[maxn];
double dp[maxn][maxn]; //dp[i][j]

double f(int i, int j) {
    if (dp[i][j] != -1) return dp[i][j];
    if (j * 2 > N) {
        return dp[i][j] = 1;    
    }
    if (i == N + 1) {
        return dp[i][j] = 0;
    }
    return dp[i][j] = p[i] * f(i+1,j+1) + (1-p[i]) * f(i+1,j);
}
    
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> p[i];
    for (int i = 1; i <= N+1; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j] = -1;
        }
    }
    double ans = f(1,0);
    cout << fixed << setprecision(10) << ans << '\n';

    return 0;
}

