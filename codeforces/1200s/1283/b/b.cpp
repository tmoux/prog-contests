#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        int d = n/k;
        int rem = n % k;
        rem = min(rem,k/2);
        int ans = d*k + rem;
        cout << ans << '\n';
    }
}

