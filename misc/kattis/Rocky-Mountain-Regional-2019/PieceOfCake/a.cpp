#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, h, v; cin >> n >> h >> v;
    ll ans = 1LL*max(h,n-h)*max(v,n-v)*4;
    cout << ans << '\n';
}

