#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int q = 1; q <= t; q++) {
        cout << "Case #" << q << ": ";
        string s; cin >> s;
        int cur = 0;
        string ans;
        for (char c: s) {
            int d = c-'0';
            while (cur > d) {
                ans += ')';
                cur--;
            }
            while (cur < d) {
                ans += '(';
                cur++;
            }
            ans += c;
        }
        while (cur > 0) {
            ans += ')';
            cur--;
        }
        cout << ans << '\n';
    }
}
