#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int r, g, b; cin >> r >> g >> b;
        vector<int> v = {r,g,b};
        sort(v.begin(),v.end());
        if (v[2] > v[0] + v[1] + 1) {
            cout << "No\n";
        }
        else {
            cout << "Yes\n";
        }
    }
}

