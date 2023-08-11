#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ceil(int a, int b) {
    return a % b == 0 ? a/b : a/b+1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b, c, d, k; cin >> a >> b >> c >> d >> k;
        int x = ceil(a,c);
        int y = ceil(b,d);
        if (x + y <= k) {
            cout << x << ' ' << y << '\n';
        }
        else {
            cout << -1 << '\n';
        }
    }
}

