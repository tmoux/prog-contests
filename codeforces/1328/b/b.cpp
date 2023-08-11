#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        for (int i = n-1, j = 1; i >= 1; i--, j++) {
            if (k > j) {
                k -= j;
            }
            else {
                string s(n,'a');
                s[i-1] = 'b';
                s[n-k] = 'b';
                cout << s << '\n';
                goto done;
            }
        }
        done:;
    }
}
