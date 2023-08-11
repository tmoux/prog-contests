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
            cin >> a[i];
        }
        bool poss = true;
        int x = 0, y = a[0];
        for (int i = 1; i < n; i++) {
            int delta = a[i]-a[i-1];
            if (delta > 0) {
                x += delta;
            }
            else if (delta < 0) {
                y += delta;
            }
            if (y < 0) poss = false;
        }
        cout << (poss?"YES":"NO") << '\n';
    }
}
