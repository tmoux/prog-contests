#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool in(int i, pair<int,int> p) {
    return p.first <= i && i <= p.second;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int l = 0, r = 1e9+9;
        vector<pair<int,int>> p;
        for (int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;
            p.push_back({a,b});
            r = min(r,b);
        }
        l = r;
        for (int i = 0; i < n; i++) {
            if (!in(r,p[i])) {
                l = max(l,p[i].first);
            }
        }
        cout << (l-r) << '\n';
    }
}

