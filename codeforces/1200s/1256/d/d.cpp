#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; ll k; cin >> n >> k;
        string s; cin >> s;
        int pos = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                int swaps = i-pos;
                if (k >= swaps) {
                    k -= swaps;
                    swap(s[i],s[pos]);
                    pos++;
                }
                else {
                    swap(s[i],s[i-k]);
                    break;
                }
            }
        }
        cout << s << '\n';
    }
}
