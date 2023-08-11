#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> p(n);
        vector<int> pos(n+1);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            pos[p[i]] = i;
        }
        int l = pos[1], r = pos[1];
        cout << 1;
        for (int i = 2; i <= n; i++) {
            l = min(l,pos[i]);
            r = max(r,pos[i]);
            if (r-l+1 == i) {
                cout << 1;
            }
            else {
                cout << 0;
            }
        }
        cout << '\n';
    }
}

