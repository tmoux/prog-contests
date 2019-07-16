#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    int c0 = 0, c1 = 0;
    for (char c: s) {
        if (c == '0') {
            c0++;
        }
        else c1++;
    }
    if (c1 != c0) {
        cout << 1 << '\n';
        cout << s << '\n';
    }
    else {
        cout << 2 << '\n';
        cout << s[0] << ' ' << s.substr(1) << '\n';
    }
}

