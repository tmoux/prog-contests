#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll x; cin >> x;
        cout << (x>14&&x%14>0&&x%14<7?"YES":"NO") << endl;
    }
}

