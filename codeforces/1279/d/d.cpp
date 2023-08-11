#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6, M = 998244353;
void madd(int& a, int b) {
    a = (a+b) % M;
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

int n;
int p[maxn], cnt[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int in = inverse(n);
    for (int i = 0; i < n; i++) {
        int k; cin >> k;
        int ik = inverse(k);
        for (int j = 0; j < k; j++) {
            int ai; cin >> ai;
            madd(p[ai],mult(in,ik));
            cnt[ai]++;
        }
    }
    int ans = 0;
    for (int i = 1; i <= 1000000; i++) {
        madd(ans,mult(p[i],mult(cnt[i],in)));
    }
    cout << ans << '\n';
}

