#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<string> s(n), t(m);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> t[i];
    }
    int q; cin >> q;
    while (q--) {
        int y; cin >> y;
        string ans;
        ans += s[(y-1)%n];
        ans += t[(y-1)%m];
        cout << ans << '\n';
    }
}

