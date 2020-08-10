#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        cout << "Case #" << q << ": ";
        int n; 
        ll d;
        cin >> n >> d;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = n-1; i >= 0; i--) {
            d = (d/a[i])*a[i];
        }
        cout << d << '\n';
    }
}

