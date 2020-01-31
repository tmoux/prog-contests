#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
}
void msub(int& a, int b) {
    madd(a,M-b);
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
const int maxn = 1003;
int N, K, a[maxn];

int dp[maxn][maxn];
map<int,int> mp;
int fac[maxn], ifac[maxn];

int perm(int n, int k) {
    assert(k <= n);
    return mult(fac[n],ifac[n-k]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    fac[0] = 1;
    ifac[0] = 1;
    for (int i = 1; i <= N; i++) {
        fac[i] = mult(fac[i-1],i);
        ifac[i] = inverse(fac[i]);
    }
    dp[0][0] = 1;
    int i = 0;
    for (auto p: mp) {
        i++;
        for (int j = 0; j <= p.second; j++) {
            for (int k = 0; j+k <= N; k++) {
                madd(dp[i][j+k],mult(dp[i-1][k],perm(p.second,j)));
            }
        }
    }
    int ans = dp[i][K];
    ans = mult(ans,inverse(perm(N,K)));
    cout << ans << '\n';
}
