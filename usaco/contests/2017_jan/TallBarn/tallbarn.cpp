#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
ll K;
ll N;
ll a[maxn];

ll count(double x) {
    ll tot = 0;
    for (int i = 1; i <= N; i++) {
        tot += (ll)((-1+sqrt(1+4*a[i]/x))/2);
    }
    return tot;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("tallbarn.in","r",stdin); freopen("tallbarn.out","w",stdout);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> a[i];
    K -= N;
        
    double lo = 0, hi = 1e18;
    for (int i = 0; i < 500; i++) {
        double m = (lo+hi)/2;
        (count(m) >= K ? lo : hi) = m;
    }

    double ans = 0;
    ll tot = 0;
    for (int i = 1; i <= N; i++) {
        ll x = (ll)((-1+sqrt(1+4*a[i]/lo))/2);
        ans += 1.0*a[i]/(x+1);
        tot += x;
    }

    cout << (ll)round(ans-(K-tot)*lo) << '\n';

    return 0;
}

