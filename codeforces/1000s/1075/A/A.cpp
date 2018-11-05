#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, x, y; cin >> n >> x >> y;
    ll d1 = max(x-1,y-1);
    ll d2 = max(n-x,n-y);
    if (d1 <= d2) {
        cout << "White" << '\n';
    }
    else {
        cout << "Black" << '\n';
    }

    return 0;
}

