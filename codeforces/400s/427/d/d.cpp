#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

set<string> a[5005], b[5005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s1, s2; cin >> s1 >> s2;
    int ans = 5005;
    for (int i = 0; i < s1.size(); i++) {
        string t = s1.substr(i) + "#" + s1;
        //cout << t << '\n';
        auto z = z_function(t);
        int mn = 1;
        for (int j = s1.size()-i+1; j < z.size(); j++) {
            if (j == s1.size()+1) continue;
            mn = max(mn,z[j]+1);
        }
        if (mn <= s1.size()-i) {
            a[mn].insert(s1.substr(i,mn));
            cout << s1.substr(i,mn) << '\n';
        }
    }
    cout << (ans > 5000 ? -1 : ans) << '\n';
}

