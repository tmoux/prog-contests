#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll l, r; cin >> l >> r;
    ll m = 0;
    for (ll i = l; i <= r; i++) {
        for (ll j = l; j <= r; j++) {
            m = max(m,i^j);
        }
    }
    cout << m << '\n';
    return 0;
}
	

