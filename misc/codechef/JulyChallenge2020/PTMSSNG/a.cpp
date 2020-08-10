#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        set<int> xs, ys;
        for (int i = 0; i < 4*n-1; i++) {
            int x, y; cin >> x >> y;
            if (xs.count(x)) xs.erase(x);
            else xs.insert(x);
            if (ys.count(y)) ys.erase(y);
            else ys.insert(y);
        }
        cout << *xs.begin() << ' ' << *ys.begin() << '\n';
    }
}
