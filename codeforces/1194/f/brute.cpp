#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5, M = 1e9+7;
int n;
ll T;
int t[maxn];

void madd(int& a, int b) {
    a = (a+b) % M;
}

int mult(int a, int b) {
    return (1LL*a*b) % M;
}

int modexp(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}

int inverse(int x) {
    return modexp(x,M-2);
}

int expp2[maxn];
int iexp2[maxn];
const int blk = 450;
int curr_last = -1;
int dp[maxn];
int fac[maxn], ifac[maxn];

int comb(int i, int j) {
    assert(0 <= j && j <= i);
    return mult(fac[i],mult(ifac[j],ifac[i-j]));
}

void filldp(int i) {
    dp[0] = 1;
    for (int k = 1; k <= i; k++) {
        dp[k] = (dp[k-1] + comb(i,k)) % M;
    }
}

int f(int i, int S) {
    //cout << "calc " << i << ' ' << S << '\n';
    if (i == S) return expp2[i];
    if (S < 0) return 0;
    int d = i-curr_last;
    //cout << "d = " << d << '\n';
    int res = 0;
    for (int k = 0; k <= d; k++) {
        if (S-k < 0) break;
        madd(res,mult(comb(d,k),dp[min(curr_last,S-k)]));
    }
    return res;
}

int p[maxn];
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> T;
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        expp2[i] = modexp(2,i);
        iexp2[i] = inverse(expp2[i]);
        fac[i] = mult(i,fac[i-1]);
        ifac[i] = inverse(fac[i]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        //cout << i << endl;
        T -= t[i];
        int S = max(min((ll)i,T),-1LL);
        int add;
        //if ((i-1) % blk == 0) {
        if (true) {
            curr_last = i;
            filldp(curr_last);
            add = S < 0 ? 0: mult(iexp2[i],dp[S]);
        }
        else {
            add = mult(iexp2[i],f(i,S));
        }
        p[i] = add;
        madd(ans,p[i]);
        //cout << i << ": " << p[i] << '\n';
    }
    cout << ans << '\n';
}

