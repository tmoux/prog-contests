#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;

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
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string curr;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        if (i == 0) {
            curr = s;
        }
        else {
            int sz = min(s.size(),curr.size());
            string a = curr.substr(curr.size()-sz);
            string b = s.substr(0,sz);
            auto z = z_function(b+'#'+a);
            int start = 0;
            for (int i = sz + 1; i < z.size(); i++) {
                if (z[i] == z.size() - i)
                    start = max(start,z[i]);
            }
            curr += s.substr(start);
        }
    }
    cout << curr << '\n';
}

