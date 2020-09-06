#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 50;
int g[maxn][maxn];
int dp[maxn][2];

int rt[maxn], lt[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i+=) {
        for (int j = 0; j < m+2; j++) {
            cin >> g[i][j];
        }
        lt[i] = 0;
        for (int j = 0; j < m+2; j++) {
            if (g[i][j]) {
                lt[i] = j;
                break;
            }
        }
        rt[i] = m+1;
        for (int j = m+1; j >= 0; j--) {
            if (g[i][j]) {
                rt[i] = j;
                break;
            }
        }
    }

    if (lt[i] == 0) {
        dp[n-1][0] = 0;
        dp[n-1][1] = m+1;
    }
    else {
        dp[n-1][0] = 2*rt[i];
        dp[n-1][1] = m+1;
    }
    for (int i = n-2; i >= 0; i--) {
        dp[i] = min(dp[i-1][0],dp[i-1]

    }
}
