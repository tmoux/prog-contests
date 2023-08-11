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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = s.size();
        bool ispal = true;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != s[n-1-i]) {
                ispal = false;
                break;
            }
        }
        if (ispal) {
            cout << s << '\n';
        }
        else {
            int l = 0, r = n-1;
            for (; l < r; l++, r--) {
                if (s[l] != s[r]) break;
            }
            string sub = s.substr(l,r-l+1);
            string rev = sub; reverse(rev.begin(),rev.end());
            string t = sub + "#" + rev;
            string mid1 = "#", mid2 = "#";
            auto z = z_function(t);
            for (int i = sub.size()+1; i < z.size(); i++) {
                if (z[i] == (int)z.size()-i) {
                    //longest palindrome found
                    mid1 = sub.substr(0,(int)z.size()-i);
                    break;
                }
            }
            t = rev + "#" + sub;
            z = z_function(t);
            for (int i = rev.size()+1; i < z.size(); i++) {
                if (z[i] == (int)z.size()-i) {
                    //mid2 found
                    mid2 = t.substr(i);
                    break;
                }
            }
            assert(mid1 != "#" && mid2 != "#");
            string st = s.substr(0,l);
            string en = st; reverse(en.begin(),en.end());
            string ans;
            if (mid1.size() >= mid2.size()) {
                ans = st + mid1 + en;
            }
            else {
                ans = st + mid2 + en;
            }
            cout << ans << '\n';
        }
    }
}
