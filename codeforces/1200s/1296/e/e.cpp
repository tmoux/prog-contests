#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ans[205];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    for (int i = 0; i < n; i++) {
        bool h0 = false, h1 = false;
        for (int j = 0; j < i; j++) {
            if (s[j] > s[i]) {
                if (ans[j] == 0) h1 = true;
                else h0 = true;
            }
        }
        if (h0 && h1) {
            cout << "NO\n";
            return 0;
        }
        if (h0) ans[i] = 0;
        else ans[i] = 1;
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cout << ans[i];
    }
    cout << '\n';
}

