#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;
int modexp(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b&1) res = (1LL*res*a) % M;
        a = (1LL*a*a) % M;
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    int ans = (modexp(2,m)-1+M) % M;
    ans = modexp(ans,n);
    cout << ans << '\n';
}

