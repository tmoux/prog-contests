#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    int ans = 0;
    while (min(n,m) > 0 && max(n,m) > 1) {
        if (n >= m && n >= 2 && m >= 1) {
            n -= 2;
            m -= 1;
            ans++;
        }
        else if (n < m && n >= 1 && m >= 2) {
            n -= 1;
            m -= 2;
            ans++;
        }
        else break;
    }
    cout << ans << endl;
}

