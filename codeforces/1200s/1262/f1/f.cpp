#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353, maxn = 2005;
int n, k;
int mult(int a, int b) {
    return (1LL*a*b) % M;
}
void madd(int& a, int b) {
    a += b;
    if (a > M) a -= M;
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

int comb[maxn][maxn];
int h[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    comb[0][0] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 0; j <= i; j++) {
            comb[i][j] = comb[i-1][j];
            if (j > 0) madd(comb[i][j],comb[i-1][j-1]);
        }
    }
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    if (k == 1) {
        cout << 0 << '\n';
        return 0;
    }
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        if (h[i] == h[(i+1)%n]) x++;
        else y++;
    }
    int ans = 0;
    for (int j = 1; j <= y; j++) {
        for (int i = 0; i < j && j+i <= y; i++) {
            int add = comb[y][j];
            add = mult(add,comb[y-j][i]);
            add = mult(add,modexp(k-2,y-i-j));
            madd(ans,add);
        }
    }
    ans = mult(ans,modexp(k,x));
    cout << ans << '\n';
}
