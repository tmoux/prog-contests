#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int a, b, c; cin >> a >> b >> c;
        vector<char> ans(n,'#');
        string s; cin >> s;
        int win = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == 'R') {
                if (b > 0) {
                    win++;
                    ans[i] = 'P';
                    b--;
                }
            }
            else if (s[i] == 'P') {
                if (c > 0) {
                    win++;
                    ans[i] = 'S';
                    c--;
                }
            }
            else {
                if (a > 0) {
                    win++;
                    ans[i] = 'R';
                    a--;
                }
            }
        }
        for (int i = 0; i < s.size(); i++) {
            if (ans[i] == '#') {
                if (a > 0) {
                    ans[i] = 'R';
                    a--;
                }
                else if (b > 0) {
                    ans[i] = 'P';
                    b--;
                }
                else {
                    assert(c > 0);
                    ans[i] = 'S';
                    c--;
                }
            }
        }
        int need = n % 2 == 0 ? n/2 : n/2+1;
        if (win >= need) {
            cout << "YES\n";
            for (char c: ans) {
                cout << c;
            }
            cout << '\n';
        }
        else {
            cout << "NO\n";
        }
    }
}

