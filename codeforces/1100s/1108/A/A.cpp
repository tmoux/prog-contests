#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
        bool swapped = false;
        if (l1 > l2) {
            swap(l1,l2);
            swap(r1,r2);
            swapped = true;
        }
        if (!swapped) cout << l1 << ' ' << r2 << '\n';                    
        else cout << r2 << ' ' << l1 << '\n';
    }


    return 0;
}

