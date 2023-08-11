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
        vector<int> ans;
        for (int i = 0; i < n; i += 2) {
            if (a[i]^a[i+1]) {
                if (!a[i]) ans.push_back(a[i]);
                if (!a[i+1]) ans.push_back(a[i+1]);
            }
            else {
                ans.push_back(a[i]);
                ans.push_back(a[i+1]);
            }
        }
        cout << ans.size() << '\n';
        for (auto i: ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
