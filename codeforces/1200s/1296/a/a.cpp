#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int c0 = 0, c1 = 0;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            if (ai&1) c1++;
            else c0++;
        }
        if (c1&1) {
            cout << "YES\n";
        }
        else {
            cout << (c0 > 0 && c1 > 0 ? "YES" : "NO") << endl;
        }
    }
}

