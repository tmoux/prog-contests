#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    const ll m = 1e9;
    ll S; cin >> S;
    ll x2 = (m - (S % m))%m;
    ll y2 = (S+x2)/m;
    assert(m*y2-x2 == S);
    cout << 0 << ' ' << 0 << ' ' << x2 << ' ' << y2 << ' ' << m << ' ' << 1 << '\n';

}

