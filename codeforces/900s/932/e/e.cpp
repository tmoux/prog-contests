#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7, maxk = 5005;
int n, k;

int mult(int a, int b) {
    return (1LL*a*b) % M;
}
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
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

int E[maxk];
int stir[maxk][maxk];

int main() {
    cin >> n >> k;
    for (int i = 0; i < maxk; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j) stir[i][j] = 1;
            else if (j > 0) {
                madd(stir[i][j],stir[i-1][j-1]);
                madd(stir[i][j],mult(j,stir[i-1][j]));
            }
        }
    }
    int curr = modexp(2,n);
    for (int i = 1; i <= k; i++) {
        curr = mult(curr,inverse(2));
        curr = mult(curr,n-i+1);
        E[i] = curr;
    }
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        madd(ans,mult(stir[k][i],E[i]));
    }
    cout << ans << endl;
}
