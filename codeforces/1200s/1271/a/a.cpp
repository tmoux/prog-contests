#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b, c, d; cin >> a >> c >> d >> b;
    int e, f; cin >> e >> f;
    int t1 = min(a,b);
    int t2 = min(b,min(c,d));
    if (e > f) {
        int ans = e*t1;
        b -= t1;
        ans += f*min(b,min(c,d));
        cout << ans << '\n';
    }
    else {
        int ans = f*t2;
        b -= t2;
        ans += e*min(a,b);
        cout << ans << '\n';
    }
}

