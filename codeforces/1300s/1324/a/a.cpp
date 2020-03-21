#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        int c0 = 0, c1 = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] % 2 == 0) c0++;
            else c1++;
        }
        if (c0 > 0 && c1 > 0) {
            cout << "NO" << endl;
        }
        else {
            cout << "YES\n";
        }
    }
}
