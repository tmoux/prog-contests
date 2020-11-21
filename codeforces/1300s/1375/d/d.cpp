#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> ans;
    auto isNondec = [&n](vector<int>& a) {
        for (int i = 1; i < n; i++) {
            if (a[i] < a[i-1]) return false;
        }
        return true;
    };
    auto mex = [&n](vector<int>& a) {
        vector<int> cnt(n+1,0);
        for (int i = 0; i < n; i++) cnt[a[i]]++;
        for (int i = 0; i <= n; i++) {
            if (cnt[i] == 0) return i;
        }
        assert(false);
    };

    while (true) {
        if (isNondec(a)) break;
        int m = mex(a);
        if (m == n) {
            for (int i = 0; i < n; i++) {
                if (a[i] != i) {
                    a[i] = m;
                    ans.push_back(i+1);
                    break;
                }
            }
        }
        else {
            a[m] = m;
            ans.push_back(m+1);
        }
    }

    cout << ans.size() << '\n';
    for (auto i: ans) {
        cout << i << ' ';
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
