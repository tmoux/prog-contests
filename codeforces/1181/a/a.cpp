#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ll x, y, z; cin >> x >> y >> z;
    if (x % z == 0 || y % z == 0) {
        cout << (x/z+y/z) << ' ' << 0 << '\n';
    }
    else {
        ll res = (x/z+y/z);
        ll move = z - max(x%z,y%z);
        ll extra = (x%z) + (y%z);
        if (extra >= z) {
            cout << (res+1) << ' ' << move << '\n';
        }
        else {
            cout << res << ' ' << 0 << '\n';
        }
    }
}

