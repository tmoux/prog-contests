#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll a, b; cin >> a >> b;
        int num = 0;
        ll mult = 10;
        while (b+1 >= mult) {
            num++;
            mult *= 10;
        }
        cout << (a*num) << '\n';
    }
}

