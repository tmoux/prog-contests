#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 998244353;
int madd(int& a, int b) {
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
int inverse(int x) {
    return modexp(x,M-2);
}

int sum(int se, int en, int diff) {
    if (se > en) return 0;
    int cnt = (en-se)/diff + 1;
    int ans = mult(2,se);
    madd(ans,mult(cnt-1,diff));
    ans = mult(ans,cnt);
    ans = mult(ans,inverse(2));
    return ans;
}

void solve() {
    int N; cin >> N;
    int res = 0;
    int diff = 2;
    int power = 0;
    while (sum(diff/2,N,diff) > 0) {
        int add = modexp(sum(diff/2,N,diff),1<<power);
        madd(res,add);
        power++;
        diff *= 2;
    }
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
