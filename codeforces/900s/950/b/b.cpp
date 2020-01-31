#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<int> x(n), y(m);
    set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        if (i > 0) x[i] += x[i-1];
        s.insert(x[i]);
    }
    int ans = 0;
    for (int i = 0; i < m; i++) {
        cin >> y[i];
        if (i > 0) y[i] += y[i-1];
        if (s.count(y[i])) ans++;
    }
    cout << ans << '\n';
}

