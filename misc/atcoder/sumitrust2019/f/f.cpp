#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll t1, t2, a1, a2, b1, b2;
    cin >> t1 >> t2 >> a1 >> a2 >> b1 >> b2;
    a1 = a1*t1;
    a2 = a2*t2;
    b1 = b1*t1;
    b2 = b2*t2;
    if (a1+a2 == b1+b2) {
        cout << "infinity\n";
        return 0;
    }
    //assume a1 < b1
    if (a1 > b1) {
        swap(a1,b1);
        swap(a2,b2);
    }
    if (a1+a2 < b1+b2) {
        //never going to happen
        cout << 0 << '\n';
    }
    else {
        ll ans = 1;
        ll diff = b1-a1;
        ll diff2 = (a1+a2)-(b1+b2);
        ll add = 2*(diff%diff2==0?diff/diff2-1:diff/diff2);
        ans += add;
        if (diff%diff2==0) ans++;
        cout << ans << '\n';
    }
}

