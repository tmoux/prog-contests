#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        string a, b;
        bool eq = true;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                a += '0';
                b += '0';
            }
            else if (s[i] == '1') {
                if (eq) {
                    a += '1';
                    b += '0';
                    eq = false;
                }
                else {
                    a += '0';
                    b += '1';
                }
            }
            else if (s[i] == '2') {
                if (eq) {
                    a += '1';
                    b += '1';
                }
                else {
                    a += '0';
                    b += '2';
                }
            }
        }
        cout << a << '\n' << b << '\n';
    }
}
