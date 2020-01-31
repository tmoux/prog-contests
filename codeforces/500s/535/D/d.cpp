#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7, maxn = 1e6+6;
int n, m;

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    string p; cin >> p;
    string s = string(n,'#');
    int curr = 0;
    vector<int> y;
    for (int i = 0; i < m; i++) {
        int yi; cin >> yi;
        yi--;
        y.push_back(yi);
        for (int j = max(curr,yi); j < n && j < yi+p.size(); j++) {
            assert(j-yi >= 0);
            s[j] = p[j-yi];
        }
        curr = yi + p.size();
    }
    auto z = z_function(p+"$"+s);
    for (int yi: y) {
        if (z[yi+p.size()+1] < p.size()) {
            cout << 0 << '\n';
            return 0;
        }
    }
    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '#') ans = (ans*26) % M;
    }
    cout << ans << '\n';
}

