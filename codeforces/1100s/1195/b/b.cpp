#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, k; cin >> n >> k;
    ll lo = -1, hi = n+1;
    ll ans = -1;
    while (lo + 1 < hi) {
        ll p = (lo+hi)/2;
        ll x = p*(p+1)/2 - (n-p);
        if (x == k) {
            ans = p;
            break;
        }
        else if (x < k) {
            lo = p;
        }
        else {
            hi = p;
        }
    }
    assert(ans != -1);
    cout << (n-ans) << '\n';
}

