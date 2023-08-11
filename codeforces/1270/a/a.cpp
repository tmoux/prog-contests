#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k1, k2; cin >> n >> k1 >> k2;
        int mx1 = 0, mx2 = 0;
        while (k1--) {
            int ai; cin >> ai;
            mx1 = max(mx1,ai);
        }
        while (k2--) {
            int ai; cin >> ai;
            mx2 = max(mx2,ai);
        }
        cout << (mx1 > mx2 ? "YES" : "NO") << endl;
    }
}

