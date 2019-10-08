#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ll sqr(int x) {
    return 1LL*x*x;
}

ld py(ld a, ld b) {
    return sqrt(a*a+b*b);
}

int main() {
    int n; cin >> n;
    while (n--) {
        int w, g, h, r; cin >> w >> g >> h >> r;
        g -= r;
        h -= r;
        ld x = h+g == 0 ? 0 : ((ld)g*w)/(ld)(h+g);
        ld maxans = py(g,x) + py(h,w-x);
        ld minans = py(abs(g-h),w);
        cout << fixed << setprecision(15) << minans << ' ' << maxans << '\n';
    }
}

