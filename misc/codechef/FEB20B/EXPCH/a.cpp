#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e7+7, M = 1e9+7;
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
int n;
string s;
int pre[maxn];
int mp[2*maxn+10];
int off = 1e7+5;

void solve() {
    cin >> n >> s;
    memset(mp,0,sizeof mp);
    for (int i = 0; i < n; i++) {
        pre[i+1] = pre[i];
        if (s[i] == '(') pre[i+1]++;
        else if (s[i] == ')') pre[i+1]--;
    }
    int ans = 0;
    for (int i = n; i >= 1; i--) {
        mp[off+pre[i]] = mp[off+pre[i]-2];
        madd(mp[off+pre[i]],n-i+1);

        madd(ans,mp[off+pre[i-1]-1]);
    }

    int den = n;
    den = mult(den,n+1);
    den = mult(den,inverse(2));
    ans = mult(ans,inverse(den));
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
