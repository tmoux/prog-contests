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
        bool found = false;
        for (int i = 0; i < n-1; i++) {
            if (abs(a[i]-a[i+1]) > 1) {
                found = true;
                cout << "YES\n";
                cout << i+1 << ' ' << i+2 << '\n';
                break;
            }
        }
        if (!found) cout << "NO\n";
    }
}

