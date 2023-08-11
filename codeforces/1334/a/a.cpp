#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<pair<int,int>> v(n);
        bool poss = true;
        int diff = 0;
        for (int i = 0; i < n; i++) {
            int p, c; cin >> p >> c;
            v[i] = {p,c};
            if (p-c < diff) {
                poss = false;
            }
            if (p < c) poss = false;
            if (i > 0 && (v[i].first < v[i-1].first || v[i].second < v[i-1].second)) {
                poss = false;
            }
            diff = p-c;
        }
        cout << (poss ? "YES" : "NO") << '\n';
    }
}

