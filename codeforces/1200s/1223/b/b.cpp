#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        string s, t; cin >> s >> t;
        map<char,int> ss, tt;
        for (char c: s) {
            ss[c]++;
        }
        bool flag = false;
        for (char c: t) {
            if (ss.count(c)) {
                cout << "YES\n";
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << "NO\n";
        }
    }
}

