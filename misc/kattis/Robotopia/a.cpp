#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//x * l1 + y * l2 = lt
//x * a1 + y * a2 = at
//[l1 l2] [x] = [lt]
//[a1 a2] [y]   [at]
//
//1/det * [a2  -l2] [lt]
//        [-a1 l1]  [at]

int main() {
    int n; cin >> n;
    while (n--) {
        ll l1, a1, l2, a2, lt, at;
        cin >> l1 >> a1 >> l2 >> a2 >> lt >> at;
        ll det = l1*a2 - l2*a1;
        ll x = a2 * lt - l2 * at;
        ll y = -a1 * lt + l1 * at;
        if (det == 0 || x % det != 0 || y % det != 0) {
            cout << "?\n";
        }
        else {
            x /= det;
            y /= det;
            assert(l1 * x + l2*y == lt && a1 * x + a2*y == at);
            if (x >= 1 && y >= 1) {
                cout << x << ' ' << y << '\n';
            }
            else {
                cout << "?\n";
            }
        }
    }
}

