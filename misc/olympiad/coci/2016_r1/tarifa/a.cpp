#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int x, n; cin >> x >> n;
    int res = 0;
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        res += x;
        res -= p;
    }
    res += x;
    cout << res << '\n';
}

