#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        int mx = 2*(k-1)-1;
        ll sum = 1+mx;
        sum = sum*(k-1)/2;
        sum = n-sum;
        if (sum&1 && sum > mx) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}

