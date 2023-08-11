#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int pfx(int x) {
    if (x == 0) return 0;
    int mult = x%2 ? -1 : 1;
    return ((x+1)/2) * mult;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    /*
    for (int i = 1; i <= 10; i++) {
        cout << i << ": " << pfx(i) << '\n';
    }
    */
    while (q--) {
        int l, r; cin >> l >> r;
        if (l == r) {
            cout << (l * (l%2?-1:1)) << '\n';
        }
        else {
            cout << (pfx(r) - pfx(l-1)) << '\n';
        }
    }

    return 0;
}

