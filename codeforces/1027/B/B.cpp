#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, q;

ll ceiling(ll a, ll b) {
    return (a % b == 0 ? a/b : a/b+1);
}

void solve() {
    ll xi, yi; cin >> xi >> yi;
    ll pre = (ll)(ceiling(n*n,2));
    if ((xi+yi) % 2 == 0) pre = 0;
    ll x;
    if ((xi-1) % 2 == 0) {
        x = (n * ((xi-1)/2)) + (yi+1)/2;
    }
    else {
        x = (n * ((xi-2)/2)) + (yi+1)/2 + n/2;
        if (n % 2 == 1 && pre == 0) x++;
    }
    cout << x + pre << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    while(q--) {
        solve();
    }

    return 0;
}
	

