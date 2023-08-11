#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int l, r, d; cin >> l >> r >> d;
        if (d < l) {
            cout << d << '\n';
        }
        else {
            int dd = (r-d)/d*d;
            while (dd <= r) dd += d;
            cout << dd << '\n';
        }
    }

    return 0;
}

