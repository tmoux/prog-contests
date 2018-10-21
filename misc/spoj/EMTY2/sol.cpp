#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    string s; cin >> s;
    int zeros = 0, ones = 0;
    if (s[0] != '1') {
        cout << "no\n";
    }
    else {
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '1') ones++;
            else zeros++;
            if (s[i] == '1') {
                if (zeros < 2) {
                    cout << "no\n";
                    return;
                }
                else zeros -= 2;
            }
        }
        cout << (zeros == 0 ? "yes" : "no") << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case " << i << ": ";
        solve();
    }
    return 0;
}

