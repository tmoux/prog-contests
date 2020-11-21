#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            char c; cin >> c;
            a[i] = c-'0';
        }
        if (n % 2 == 1) {
            bool hasOdd = false;
            for (int i = 0; i < n; i += 2) {
                if (a[i] % 2 == 1) {
                    hasOdd = true;
                }
            }
            cout << (hasOdd?1:2) << '\n';
        }
        else {
            bool hasEven = false;
            for (int i = 1; i < n; i += 2) {
                if (a[i] % 2 == 0) {
                    hasEven = true;
                }
            }
            cout << (hasEven?2:1) << '\n';
        }
    }
}
