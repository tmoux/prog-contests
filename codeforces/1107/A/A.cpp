#include <bits/stdc++.h>
using namespace std;
using ll = long long;



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        string s; cin >> s;
        if (s.size() == 2) {
            if (s[0] < s[1]) {
                cout << "YES\n";
                cout << "2\n " << s[0] << ' ' << s[1] << '\n';
            }
            else {
                cout << "NO\n";
            }
        }
        else {
            cout << "YES\n";
            cout << 2 << '\n';
            cout << s[0] << ' ' << s.substr(1) << '\n';
        }
    }

    return 0;
}

