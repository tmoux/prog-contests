#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 100005;
int n, bit[maxn];
//reversed for loops, so sum is [1..x]
void add(int i, int x) {
    for (; i; i -= i & (-i)) {
        bit[i] += x;
        //cout << i << ' ' << x << '\n';
    }
}

int sum(int i) {
    int r = 0;
    for (; i <= n; i += i & (-i)) {
        r += bit[i];
    }
    return r;
}

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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    n = s.size();
    auto z = z_function(s);
    for (int i = 0; i < n; i++) {
        if (z[i] > 0) {
            add(z[i],1);
            //cout << z[i] << '\n';
        }
    }
    /*
    for (int i = 1; i <= 8; i++) {
        cout << i << ": " << sum(i) << '\n';
    }
    */
    vector<pair<int,int>> ps;
    for (int i = n-1; i >= 0; i--) {
        if (i == 0 || z[i] == n-i) {
            ps.push_back({n-i,sum(n-i)+1});
        }
    }
    cout << ps.size() << '\n';
    for (auto p: ps) {
        cout << p.first << ' ' << p.second << '\n';
    }
}

