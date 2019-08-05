#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
ll n, a[maxn];
ll k;

bool check(ll x) {
    ll need = 0;
    for (ll i = n/2; i < n; i++) {
        if (a[i] < x) need += x-a[i];
    }
    //cout << x << ": " << need << '\n';
    return need <= k;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a,a+n);
    ll lo = a[n/2], hi = 5e9+9;
    /*
    for (ll i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }
    return 0;
    */
    while (lo + 1 < hi) {
        ll mid = (lo+hi)/2;
        //cout << mid << ": " << check(mid) << '\n';
        if (check(mid)) {
            lo = mid;
        }
        else hi = mid;
    }
    cout << lo << '\n';
}

