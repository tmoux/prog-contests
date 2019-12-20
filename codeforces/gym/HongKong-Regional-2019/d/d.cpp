#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int k, X; cin >> k >> X;
        X--;
        ll count = k;
        int dig = 1;
        while (X >= count) {
            X -= count;
            dig++;
            count *= k;
        }
        vector<int> ret;
        for (int i = 0; i < dig; i++) {
            ret.push_back(X%k);
            X /= k;
        }
        reverse(ret.begin(),ret.end());
        for (int i: ret) {
            cout << (i+(10-k));
        }
        cout << '\n';
    }
}

