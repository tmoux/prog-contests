#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) begin(x),end(x)

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n, r; cin >> n >> r;
        vector<int> x(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i];
        }
        sort(all(x));
        x.erase(unique(all(x)),x.end());
        for (int i = x.size()-1, num = 1; i >= 0; i--, num++) {
            if (i == 0 || (ll)x[i-1]-(ll)num*r <= 0) {
                cout << num << '\n';
                break;
            }
        }
    }
}

