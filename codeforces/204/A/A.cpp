#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll expo(ll b, ll n) {
    ll res = 1;
    for (ll i = 0; i < n; i++) res *= b;
    return res;
}

ll f(ll i, ll k) {
    //k is # of digits
    return i*expo(10,max(0LL,k-2));
}

ll calc(ll x) {
    if (x < 10) return x;
    ll d = x;
    ll k = 0;
    ll msDigit;
    while (d) {
        msDigit = d;
        k++;
        d /= 10;
    }
    //k is the # of digits
    ll res = f(msDigit-1,k);
    for (ll i = 1; i < k; i++) res += f(9,i);
    if (k >= 2) {
        d = x;
        d -= msDigit*expo(10,k-1); d /= 10;
        res += (x%10 >= msDigit ? d+1 : d);
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll l, r; cin >> l >> r;
    cout << (calc(r) - calc(l-1)) << '\n';
    return 0;
}

