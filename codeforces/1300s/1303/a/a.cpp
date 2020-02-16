#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int fi = -1, si = -1;
        int c1 = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') {
                if (fi == -1) fi = i;
                si = i;
                c1++;
            }
        }
        if (c1 == 0) {
            cout << 0 << '\n';
        }
        else {
            int ans = (si-fi+1) - c1;
            cout << ans << '\n';
        }
    }
}

