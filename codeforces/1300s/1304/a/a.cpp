#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int x, y, a, b; cin >> x >> y >> a >> b;
        int d = y-x;
        if (d % (a+b) != 0) {
            cout << -1 << '\n';
        }
        else {
            cout << (d/(a+b)) << endl;
        }
    }
}
