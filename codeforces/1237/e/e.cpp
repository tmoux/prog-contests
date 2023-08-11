#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6, M = 998244353;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int x = 1;
    while (x <= n) {
        if (x == n || x+1 == n) {
            cout << 1 << '\n';
            return 0;
        }
        if (x&1) x = 2*x + 2;
        else x = 2*x + 1;
    }
    cout << 0 << '\n';
}

