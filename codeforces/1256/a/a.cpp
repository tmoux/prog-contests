#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int a, b, n, S; cin >> a >> b >> n >> S;
        int div = S/n;
        S -= min(a,div) * n;
        cout << (S <= b ? "Yes" : "No") << '\n';
    }
}

