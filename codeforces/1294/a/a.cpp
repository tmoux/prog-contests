#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b, c, n; cin >> a >> b >> c >> n;
        if ((a+b+c+n) % 3 != 0) {
            cout << "NO\n";
        }
        else {
            vector<int> v = {a,b,c};
            sort(v.begin(),v.end());
            if ((v[2]-v[1])+(v[2]-v[0]) > n) {
                cout << "NO\n";
            }
            else {
                cout << "YES\n";
            }
        }
    }
}

