#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 51, M = 1e9+7;
void madd(int& a, int b) {
    a = (a+b)%M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
ll modexp(int a, int p) {
    int res = 1;
    while (p) {
        if (p&1) {
            res = mult(res,a);
            a = mult(a,a);
            p >>= 1;
        }
    }
    return res;
}
int n, T;
int t[maxn], g[maxn];
ll fac[maxn], ifac[maxn];
int dp[3][2505];

int comb(const vector<int>& v) {
    int a = v[0], b = v[1], c = v[2];
    int r = mult(fac[a+b+c],ifac[a]);
    r = mult(r,ifac[b]);
    r = mult(r,ifac[c]);
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> T;
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = mult(i,fac[i-1]);
    }
    ifac[0] = 1;
    for (int i = 1; i <= n; i++) {
        ifac[i] = modexp(fac[i],M-2);
    }
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> g[i];
    }
    int m = n/2;
    for (int i = 0; i < (1<<m); i++) {
        vector<int> cnt(3);
        int ti = 0;
        for (int j = 0; j < m; j++) {
            if (i&(1<<j)) {
                cnt[g[j]]++;
                ti += t[j];
            }
        }
        for (int j = 0; j < 3; j++) {
            if (cnt[j] > 0) {
                cnt[j]--;
                madd(dp[j][ti],mult(cnt[j]+1,comb(cnt)));
                cnt[j]++;
            }
        }
    }
    dp[0][0] = dp[1][0] = dp[2][0] = 1;
    int ans = 0;
    for (int i = 0; i < (1<<(n-m)); i++) {
        vector<int> cnt(3);
        int ti = 0;
        for (int j = 0; j < (n-m); j++) {
            if (i&(1<<j)) {
                cnt[g[j+m]]++;
                ti += t[j+m];
            }
        }
        if (ti <= T) {
            for (int j = 0; j < 3; j++) {
                int need = T-ti;

            }
        }
    }
}

