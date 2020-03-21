#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const int maxn = 18;
int n;
ld p[maxn][maxn];
ld dp[1<<maxn][maxn];

ld f(int mask, int i) {
    ld& res = dp[mask][i];
    if (res > -0.9) return res;
    if (mask == (1<<n)-1) return res = i==0?1:0;
    res = 0;
    for (int j = 0; j < n; j++) {
        if (!(mask & (1<<j))) {
            ld cur = 0;
            cur += f(mask|(1<<j),i) * p[i][j];
            cur += f(mask|(1<<j),j) * p[j][i];
            res = max(res,cur);
        }
    }
    return res;
}

int main() {
    cin >> n;
    if (n == 1) {
        cout << "1.0\n";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> p[i][j];
        }
    }
    for (int i = 0; i < (1<<maxn); i++) {
        for (int j = 0; j < maxn; j++) {
            dp[i][j] = -1.0;
        }
    }
    ld ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int mask = (1<<i) | (1<<j);
            ld cur = 0;
            cur += f(mask,i) * p[i][j];
            cur += f(mask,j) * p[j][i];
            ans = max(ans,cur);
        }
    }
    cout << fixed << setprecision(10) << ans << '\n';
}
