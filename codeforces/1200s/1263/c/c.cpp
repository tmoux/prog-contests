#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        set<int> s;
        int curr = 1;
        while (curr <= n) {
            int lo = curr, hi = n+1;
            while (lo + 1 < hi) {
                int mid = (lo+hi)/2;
                if (n/mid == n/curr) {
                    lo = mid;
                }
                else {
                    hi = mid;
                }
            }
            s.insert(n/curr);
            curr = lo + 1;
        }
        s.insert(0);
        cout << s.size() << '\n';
        for (auto i: s) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}

