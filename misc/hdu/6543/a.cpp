#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s, t;
    while (cin >> s >> t) {
        if (s == t) {
            cout << "Equal" << '\n';
        }
        else if (s.size() == t.size() && s[0] == t[0] &&
                 s.back() == t.back()) {
            cout << "Yes" << '\n';
        }
        else cout << "No" << '\n';
    }

}

