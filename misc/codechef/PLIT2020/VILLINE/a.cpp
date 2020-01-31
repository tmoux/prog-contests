#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
ll m, c;
ll eval(ll x) {
    return m*x+c;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> c;
    ll over = 0, under = 0;
    for (int i = 0; i < n; i++) {
        ll x, y, p; cin >> x >> y >> p;
        if (y > eval(x)) {
            over += p;
        }
        else under += p;
    }
    cout << max(over,under) << '\n';
}

