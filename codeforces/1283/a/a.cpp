#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int h, m; cin >> h >> m;
        int ans = 0;
        if (m != 0) {
            ans += 60-m;
            h++;
        }
        ans += 60*(24-h);
        cout << ans << endl;
    }
}

