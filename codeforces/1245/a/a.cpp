#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        int gc = __gcd(a,b);
        if (gc == 1) {
            cout << "Finite\n";
        }
        else {
            cout << "Infinite\n";
        }
    }
}

