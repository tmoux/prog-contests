#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 5005, M = 998244353;
void madd(int& a, int b) {
    a += b;
    if (a > M) a -= M;
}
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
int a, b, c;
int ch[maxn][maxn];
int fac[maxn];

int f(int a, int b) {
    int res = 0;
    for (int i = 0; i <= min(a,b); i++) {
        madd(res,mult(mult(ch[a][i],ch[b][i]),fac[i]));
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> a >> b >> c;
    ch[0][0] = 1;
    fac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = mult(fac[i-1],i);
        for (int j = 0; j <= i; j++) {
            if (j == 0) ch[i][j] = ch[i-1][j];
            else {
                ch[i][j] = ch[i-1][j-1];
                madd(ch[i][j],ch[i-1][j]);
            }
        }
    }
    int ans = 1;
    ans = mult(ans,f(a,b));
    ans = mult(ans,f(c,b));
    ans = mult(ans,f(c,a));
    cout << ans << '\n';
}

