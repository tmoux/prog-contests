#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ld pi = atan(1)*4;

ld calc(ld a, ld theta) {
    return (a*a)/2*(1/tan(theta));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b, x; cin >> a >> b >> x;
    ld area = x/(ld)a;
    //cout << "area = " << area << '\n';
    ld lo = 0, hi = pi/2;
    for (int i = 0; i < 100; i++) {
        ld mid = (lo+hi)/2;
        ld ca = calc(a,pi/2-mid);
        ld cb = calc(b,mid);
        //cout << mid << ": " << (a*b)-min(ca,cb) << '\n';
        ld cmp = area <= (ld)(a*b)/2 ? min(ca,cb) : (ld)a*b-min(ca,cb);
        if (cmp <= area) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
    cout << fixed << setprecision(15) << (lo*180/pi) << '\n';
}

