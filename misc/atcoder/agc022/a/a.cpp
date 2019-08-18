#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; cin >> s;
    if (s.size() < 26) {
        set<char> seen;
        for (char c: s) {
            seen.insert(c);
        }
        for (char c = 'a'; c <= 'z'; c++) {
            if (!seen.count(c)) {
                s += c;
                cout << s << '\n';
                return 0;
            }
        }
    }
    else {
        set<char> seen;
        for (int i = s.size() - 1; i >= 0; i--) {
            seen.insert(s[i]);
            if (seen.upper_bound(s[i]) != seen.end()) {
                auto it = seen.upper_bound(s[i]);
                string res = s.substr(0,i) + *it;
                cout << res << '\n';
                return 0;
            }
        }
        cout << -1 << endl;
    }
}

