#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, x, a, b; cin >> n >> x >> a >> b;
        int d = abs(a-b);
        d += x;
        d = min(d,n-1);
        cout << d << '\n';
    }
}

