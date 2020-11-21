#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll ceil(ll a, ll b) {
    return (a+b-1)/b;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll x, y, k; cin >> x >> y >> k;
        ll A = ceil(k*(y+1)-1,x-1);
        A += k;
        cout << A << '\n';
    }
}
