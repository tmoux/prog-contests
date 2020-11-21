#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int r, e, c; cin >> r >> e >> c;
        if (r > e - c) {
            cout << "do not advertise\n";
        }
        else if (r == e - c) {
            cout << "does not matter\n";
        }
        else {
            cout << "advertise\n";
        }
    }
}

