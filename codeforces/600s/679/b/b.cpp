#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll cube(int x) {
    return 1LL*x*x*x;
}

ll m;

pair<ll,ll> ans;
void f(ll m, ll cnt, ll s) {
    if (m == 0) {
        ans = max(ans,{cnt,s});
        return;
    }
    ll x = 1;
    while (cube(x+1) <= m) x++;
    f(m-cube(x),cnt+1,s+cube(x));
    if (x >= 1) f(cube(x)-1-cube(x-1),cnt+1,s+cube(x-1));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> m;
    f(m,0,0);
    cout << ans.first << ' ' << ans.second << '\n';
}

