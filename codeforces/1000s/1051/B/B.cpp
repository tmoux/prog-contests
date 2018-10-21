#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll l, r; cin >> l >> r;
    cout << "YES" << '\n';
    for (; l<r;l+=2) {
        cout << l << ' ' << l+1 << '\n';
    }

    return 0;
}

