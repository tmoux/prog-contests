#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
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
int inverse(int x) {
    return modexp(x,M-2);
}
const int maxn = 2600;
int ch[maxn][maxn];

int f(int N, int n, int r) {
    int ans = 0;
    for (int q = 0; q <= min(n,N/(r+1)); q++) {
        int add = (q&1) ? M-1 : 1;
        add = mult(add,ch[n][q]);
        add = mult(add,ch[N-q*(r+1)+n-1][n-1]);
        madd(ans,add);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for (int i = 0; i < maxn; i++) {
        ch[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            ch[i][j] = ch[i-1][j-1];
            ch[i][j] += ch[i-1][j];
            ch[i][j] %= M;
        }
    }
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = 0;
        for (char c: s) {
            n += c-'a';
        }
        int ans = f(n,s.size(),25);
        madd(ans,M-1);
        cout << ans << '\n';
    }
}

