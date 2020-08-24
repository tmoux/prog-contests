#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 205;
int R, G, B;
int r[maxn], g[maxn], b[maxn];

int dp[maxn][maxn][maxn];
int f(int i, int j, int k) {
    int& res = dp[i][j][k];
    if (res != -1) return res;
    res = 0;
    if (i > 0 && j > 0) res = max(res,r[i]*g[j]+f(i-1,j-1,k));
    if (i > 0 && k > 0) res = max(res,r[i]*b[k]+f(i-1,j,k-1));
    if (j > 0 && k > 0) res = max(res,g[j]*b[k]+f(i,j-1,k-1));
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> R >> G >> B;
    for (int i = 1; i <= R; i++) {
        cin >> r[i];
    }
    for (int i = 1; i <= G; i++) {
        cin >> g[i];
    }
    for (int i = 1; i <= B; i++) {
        cin >> b[i];
    }
    sort(r+1,r+R+1);
    sort(g+1,g+G+1);
    sort(b+1,b+B+1);
    memset(dp,-1,sizeof dp);
    int ans = f(R,G,B);
    cout << ans << '\n';
}
