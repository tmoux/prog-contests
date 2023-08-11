#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        auto spf = [&](int x) {
            for (int i = 2; i*i <= x; i++) {
                if (x % i == 0) return i;
            }
        };
        map<int,vector<int>> mp;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mp[spf(a[i])].push_back(i);
        }
        vector<int> ans(n);
        int i = 1;
        for (auto p: mp) {
            for (auto j: p.second) {
                ans[j] = i;
            }
            i++;
        }
        cout << mp.size() << '\n';
        for (int i = 0; i < n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}
