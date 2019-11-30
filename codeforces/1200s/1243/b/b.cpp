#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        string s, t; cin >> s >> t;
        vector<int> diff;
        for (int i = 0; i < n; i++) {
            if (s[i]!=t[i]) diff.push_back(i);
        }
        if (diff.size() != 2) {
            cout << "No\n";
        }
        else {
            if (s[diff[0]] == s[diff[1]] &&
                t[diff[0]] == t[diff[1]]) {
                cout << "Yes\n";
            }
            else {
                cout << "No\n";
            }
        }
    }
}

