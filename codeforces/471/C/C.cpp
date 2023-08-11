#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n; cin >> n;
    ll kmin = 3 - n%3;
    ll d = (ll)sqrt((ld)(1+24*n));
    ll kmax = (d-1)/6;
    cout << (kmax-kmin+3)/3 << '\n';

    return 0;
}

