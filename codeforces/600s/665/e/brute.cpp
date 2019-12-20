#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int a[1000006];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] ^= a[i-1];
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if ((a[i] ^ a[j]) >= k) ans++;
        }
    }
    cout << ans << '\n';
}

