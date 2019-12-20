#include <bits/stdc++.h>
using namespace std;
using ll = long long;

char other(char a, char b) {
    if (a != 'a' && b != 'a') return 'a';
    if (a != 'b' && b != 'b') return 'b';
    if (a != 'c' && b != 'c') return 'c';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = s.size();
        s = '?' + s + '?';
        for (int i = 1; i < s.size()-1; i++) {
            if (s[i] == '?') {
                s[i] = other(s[i-1],s[i+1]);
            }
        }
        bool poss = true;
        for (int i = 1; i < s.size()-2; i++) {
            if (s[i] == s[i+1]) {
                poss = false;
                break;
            }
        }
        if (!poss) {
            cout << -1 << '\n';
        }
        else {
            cout << s.substr(1,n) << '\n';
        }
    }
}

