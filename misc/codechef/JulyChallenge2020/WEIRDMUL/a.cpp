#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
const int M = 998244353;
void madd(int& a, int b) {
    a += b;
    if (a >= M) a -= M;
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
int sqr(int x) {
    return mult(x,x);
}
int N, X;
int A[maxn];

void solve() {
    cin >> N >> X;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    int ans = 1;
    int cur = 0;
    for (int i = 1; i <= N; i++) {
        cur = mult(cur,X);
        madd(cur,1);
        int m = modexp(mult(cur,A[0]),N-i+1);
        ans = mult(ans,m);
    }
    ans = sqr(ans);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
