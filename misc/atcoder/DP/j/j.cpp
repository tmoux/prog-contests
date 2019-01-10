#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 305;
int N; 
double dp[maxn][maxn][maxn];
int c[4];

double f(int c1, int c2, int c3) {
    //if (c1 < 0 || c2 < 0 || c3 < 0) return 0;
    if (c1 == 0 && c2 == 0 && c3 == 0) return 0;
    double& res = dp[c1][c2][c3];
    if (res != -1) return res;
    res = 1;
    if (c1 > 0) res += 1.0*c1/N*f(c1-1,c2,c3);      
    if (c2 > 0) res += 1.0*c2/N*f(c1+1,c2-1,c3);
    if (c3 > 0) res += 1.0*c3/N*f(c1,c2+1,c3-1);
    if (c1 + c2 + c3 < N) res = (res * N) / (1.0 * c1 + c2 + c3);
    //cout << c1 << ' ' << c2 << ' ' << c3 << ": " << res << '\n';
    return res; 
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int ai; cin >> ai;
        c[ai]++;
    }
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            for (int k = 0; k < maxn; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
    double ans = f(c[1],c[2],c[3]);
    cout << fixed << setprecision(12) << ans << '\n';


    return 0;
}

