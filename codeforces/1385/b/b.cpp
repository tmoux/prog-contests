#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        set<int> seen;
        vector<int> p;
        for (int i = 0; i < 2*n; i++) {
            int ai; cin >> ai;
            if (!seen.count(ai)) {
                p.push_back(ai);
                seen.insert(ai);
            }
        }
        assert(p.size() == n);
        for (int i: p) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}

