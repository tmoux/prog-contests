#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        vector<int> v(3);
        cin >> v[0] >> v[1] >> v[2];
        sort(v.begin(),v.end());
        if (v[2] == v[1] && v[1] >= v[0]) {
            //a = x, b = c = z
            cout << "YES\n";
            cout << v[0] << ' ' << v[0] << ' ' << v[2] << '\n';
        }
        else {
            //all distinct
            cout << "NO" << '\n';
        }
    }
}
