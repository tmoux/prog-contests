#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int solve(ll k, ll n, ll a, ll b) {
    if (n*b >= k) return -1;
    ll lo = 0, hi = n+1;
    while (lo + 1 < hi) {
        ll mid = (lo+hi)/2;
        if (mid*a+(n-mid)*b < k) {
            lo = mid;
        }
        else hi = mid;
    }
    return lo;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int q; cin >> q;
    while (q--) {
        int k, n, a, b; cin >> k >> n >> a >> b;
        cout << solve(k,n,a,b) << '\n';
    }

}

