#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
int msub(int a, int b) {
    madd(a,M-b);
    return a;
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
int inverse(int x) {
    return modexp(x,M-2);
}
const int maxn = 5005;
int dp[2][maxn];

int n, a, b, K;

int main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> a >> b >> K;
    dp[0][a] = 1;
    for (int k = 1; k <= K; k++) {
        int o = k&1;
        //prefix sums
        for (int x = 1; x <= n; x++) {
            madd(dp[o^1][x],dp[o^1][x-1]);
        }
        for (int x = 1; x <= n; x++) {
            dp[o][x] = 0;
            if (x == b) continue;
            int l, r;
            if (x < b) {
                r = x + (b-x-1)/2;
                l = 1;
            }
            else if (x > b) {
                l = x - (x-b-1)/2;
                r = n;
            }
            else assert(false);
            dp[o][x] = msub(dp[o^1][r],dp[o^1][l-1]);
            dp[o][x] = msub(dp[o][x],msub(dp[o^1][x],dp[o^1][x-1]));
            //printf("[%d][%d]: %d\n",k,x,dp[o][x]);
        }
    }
    int ans = 0;
    for (int x = 1; x <= n; x++) {
        //cout << x << ": " << dp[K&1][x] << '\n';
        madd(ans,dp[K&1][x]);
    }
    cout << ans << '\n';
}

