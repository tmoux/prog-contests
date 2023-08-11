#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505;
int n, m, mod;
void madd(int& a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}
int mult(int a, int b) {
    return (1LL*a*b) % mod;
}

int dp[maxn][maxn];
int col[maxn];
int ch[maxn][maxn];

int ch2(int x) {
    return x*(x-1)/2;
}

int f(int i, int j) {
    int& res = dp[i][j];
    if (res != -1) return res;
    res = 0;
    if (i > 0 && j > 0) madd(res,mult(f(i,j-1),mult(i,j))); 
    if (j > 1) madd(res,mult(f(i+2,j-2),ch2(j))); 
    if (i > 1) madd(res,mult(f(i-2,j),ch2(i))); 
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> mod;
    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '1') col[j]++;
        }
    }
    /*
    for (int i = 0; i <= n; i++) {
        ch[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            madd(ch[i][j],ch[i-1][j-1]);
            madd(ch[i][j],ch[i-1][j]);
        }
    }
    */
    int n1 = 0, n2 = 0;
    for (int i = 0; i < n; i++) {
        if (col[i] == 0) n2++;
        else if (col[i] == 1) n1++;
        else if (col[i] > 2) {
            assert(false);
        }
    }
    memset(dp,-1,sizeof dp);
    dp[0][0] = 1;
    cout << f(n1,n2) << '\n';
}

