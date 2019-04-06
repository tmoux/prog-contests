#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll N;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    ll mn = max(1LL,(ll)(sqrt(N/2)-1));
    ll mx = sqrt(N) + 2;
    ll ans = 1e18;
    for (ll x = mn; x <= mx; x++) {
        ll y = N % x == 0 ? N/x : N/x+1;
        if (x/2 <= y && y <= 2*x) {
            ans = min(ans,x*y-N);
        }
    }
    cout << ans << '\n';
}

