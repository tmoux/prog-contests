#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
int N, A, B, C, D;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

int dp[1005][1005];
int ch[1005][1005];
int part[1005][1005];
int inv[1005];

int main() {
    scanf("%d %d %d %d %d",&N,&A,&B,&C,&D);
    for (int i = 1; i <= N; i++) {
        inv[i] = modexp(i,M-2);
    }
    for (int i = 0; i <= N; i++) {
        ch[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            madd(ch[i][j],ch[i-1][j]);
            madd(ch[i][j],ch[i-1][j-1]);
        }
    }
    for (int j = 1; j <= N; j++) part[0][j] = 1;
    for (int n = 1; n <= N; n++) {
        for (int j = 1; j <= n; j++) {
            if (n % j == 0) {
                part[n][j] = mult(ch[n][j],part[n-j][j]);
                part[n][j] = mult(part[n][j],inv[n/j]);
            }
        }
    }
    for (int i = 0; i <= N+1; i++) dp[0][i] = 1;
    for (int i = B; i >= A; i--) {
        for (int n = 1; n <= N; n++) {
            dp[n][i] = dp[n][i+1];
            for (int j = C*i; n-j >= 0 && j <= D*i; j += i) {
                int ways = mult(ch[n][j],part[j][i]);
                madd(dp[n][i],mult(ways,dp[n-j][i+1]));
            }
        }
    }
    printf("%d\n",dp[N][A]);
}

