#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e3+3;
int n, m, A[maxn][maxn], d[4][maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> A[i][j];
        }
    }

    //fill d
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            d[0][i][j] = max(d[0][i-1][j],d[0][i][j-1]) + A[i][j];
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = m; j >= 1; j--) {
            d[1][i][j] = max(d[1][i+1][j],d[1][i][j+1]) + A[i][j];
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            d[2][i][j] = max(d[2][i+1][j],d[2][i][j-1]) + A[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            d[3][i][j] = max(d[3][i-1][j],d[3][i][j+1]) + A[i][j];
        }
    }
    //calculate maximum
    int res = 0;
    for (int i = 2; i <= n-1; i++) {
        for (int j = 2; j <= m-1; j++) {
            int c1 = d[0][i-1][j] + d[1][i+1][j] + d[2][i][j-1] + d[3][i][j+1];
            int c2 = d[0][i][j-1] + d[1][i][j+1] + d[2][i+1][j] + d[3][i-1][j];
            res = max(res,max(c1,c2));
        }
    }

    cout << res << '\n';

    return 0;
}
	

