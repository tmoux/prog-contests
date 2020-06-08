#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    ll tot = 0;
    for (int i = 0; i < m; i++) {
        int ai; cin >> ai;
        tot += ai;
    }
    if (tot > n) {
        cout << -1 << '\n';
    }
    else cout << (n-tot) << '\n';
}
