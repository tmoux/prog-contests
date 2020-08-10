#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t, n; cin >> t >> n;
    cout << t << '\n';
    while (t--) {
        cout << n << '\n';
        for (int i = 0; i < n; i++) {
            int r = rand() % 10000 + 1;
            cout << r << ' ';
        }
        cout << '\n';
    }
}
