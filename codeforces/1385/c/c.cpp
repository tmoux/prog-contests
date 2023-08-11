#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int i = n-1;
        while (i-1 >= 0 && a[i-1] >= a[i]) i--;
        while (i-1 >= 0 && a[i-1] <= a[i]) i--;
        cout << i << '\n';
    }
}
