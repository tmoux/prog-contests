#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> v(n,9);
        int num = (n+3)/4;
        for (int i = 0; i < num; i++) {
            v[i] = 8;
        }
        reverse(v.begin(),v.end());
        for (int i = 0; i < n; i++) {
            cout << v[i];
        }
        cout << '\n';
    }
}
