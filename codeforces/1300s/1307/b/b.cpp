#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, x; cin >> n >> x;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        bool done = false;
        for (int i = 0; i < n; i++) {
            if (a[i] == x) {
                cout << 1 << '\n';
                done = true;
                break;
            }
        }
        if (!done) {
            sort(a.begin(),a.end());
            int mx = a.back();
            cout << max(2,(x+mx-1)/mx) << endl;
        }
    }
}

