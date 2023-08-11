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
        multiset<int> l, r;
        l.insert(a[0]);
        for (int i = 1; i < n; i++) r.insert(a[i]);
        for (int i = 1; i < n-1; i++) {
            auto it = r.find(a[i]);
            r.erase(it);
            for (auto j: l) {
                if (r.count(j)) {
                    cout << "YES\n";
                    goto done;
                }
            }
            l.insert(a[i]);
        }
        cout << "NO\n";
        done: ;
    }
}
