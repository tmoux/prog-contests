#include <bits/stdc++.h>
using namespace std;
typedef long long ll;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    cout << n << ' ' << q << '\n';
    while (q--) {
        int t = rand() % 2;
        if (t == 0) {
            int l = rand() % n;
            int r = rand() % n;
            if (l > r) swap(l,r);
            cout << 0 << ' ' << l << ' ' << r << '\n';
        }
        else {
            int i = rand() % n;
            int x = rand() % 1000;
            cout << 1 << ' ' << i << ' ' << x << '\n';
        }
    }

    return 0;
}

