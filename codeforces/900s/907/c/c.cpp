#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;

//. no electric shock
//! is shock
//? guess

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    set<char> poss;
    for (char c = 'a'; c <= 'z'; c++) {
        poss.insert(c);
    }
    int cnt = 0;
    while (n--) {
        if (n == 0) continue;
        char c; string s; cin >> c >> s;
        if (c == '!') {
            if (poss.size() == 1) cnt++;
            set<char> ns;
            for (char c: s) {
                if (poss.count(c)) {
                    ns.insert(c);
                }
            }
            poss = ns;
        }
        else if (c == '.') {
            for (char c: s) {
                if (poss.count(c)) {
                    poss.erase(c);
                }
            }
        }
        else if (c == '?') {
            if (poss.size() == 1) cnt++;
            char d = s[0];
            if (poss.count(d)) {
                poss.erase(d);
            }
        }
    }
    cout << cnt << '\n';
}

