#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, a, b; cin >> n >> a >> b;
        for (int i = 0; i < n; i++) {
            cout << (char)(i%b+'a');
        }
        cout << '\n';
    }
}
