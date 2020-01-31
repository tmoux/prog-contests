#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
int n, m;
int d[maxn];

ll ch2(int x) {
    return 1LL*x*(x-1)/2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        d[a]++; d[b]++;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += 2*ch2(d[i])+2*ch2(n-1-d[i])-1LL*d[i]*(n-1-d[i]);
    }
    cout << ans/6 << '\n';
}

