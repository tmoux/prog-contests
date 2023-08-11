#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        if (a > b) swap(a,b);
        if (b > 2*a) {
            cout << "NO\n";
        }
        else {
            if ((a+b) % 3 == 0) {
                cout << "YES" << '\n';
            }
            else {
                cout << "NO\n";
            }
        }
    }
}

