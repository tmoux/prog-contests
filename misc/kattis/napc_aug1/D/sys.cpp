#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 505;
int n, m, U[N][N], D[N][N];
bool v[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            D[i][j] = n + 1, U[i][j] = 0;
    ll ans = (1ll * n * (n + 1) * m * (m + 1)) >> 2;
    for (int i = 1, x, y; i <= n * m; i++) {
        scanf("%d%d", &x, &y);
        for (int l = y, ul = 1, dl = n; l >= 1 && !v[x][l]; l--) {
            dl = min(dl, D[x][l] - 1), ul = max(ul, U[x][l] + 1);
            for (int r = y, u = ul, d = dl; r <= m && !v[x][r]; r++) {
                d = min(d, D[x][r] - 1), u = max(u, U[x][r] + 1);
                ans -= 1ll * (x - u + 1) * (d - x + 1);
            }
        }
        printf("%lld\n", ans);
        for (int j = x - 1; j >= 1 && !v[j][y]; j--)D[j][y] = x;
        for (int j = x + 1; j <= n && !v[j][y]; j++)U[j][y] = x;
        v[x][y] = true;
    }
    return 0;
}
