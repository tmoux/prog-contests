#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        int diff = abs(a-b);
        int ans = diff/5;
        diff %= 5;
        ans += diff/2;
        diff %= 2;
        ans += diff;
        cout << ans << '\n';
    }
}

