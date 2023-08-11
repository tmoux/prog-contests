#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        int x, y, x1, y1, x2, y2; cin >> x >> y >> x1 >> y1 >> x2 >> y2;
        x1 -= x; x2 -= x;
        y1 -= y; y2 -= y;
        bool poss = true;
        if (x1 == x2) {
            if (a != 0 || b != 0) poss = false;
        }
        else {
            if (x1 > b-a || x2 < b-a) poss = false;
        }
        if (y1 == y2) {
            if (c != 0 || d != 0) poss = false;
        }
        else {
            if (y1 > d-c || y2 < d-c) poss = false;
        }
        cout << (poss ? "YES" : "NO") << '\n';
    }
}
