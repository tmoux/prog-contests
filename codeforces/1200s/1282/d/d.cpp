#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int ask(const string& s) {
    assert(!s.empty());
    cout << s << endl;
    int x; cin >> x;
    if (x == 0 || x == -1) exit(0);
    return x;
}

char other(char c) {
    return c == 'a' ? 'b' : 'a';
}

int main() {
    int x, y;
    x = ask(string(300,'a'));
    y = ask(string(300,'b'));
    int nA = 300-x;
    int nB = 300-y;
    int L = 300-x+300-y;
    string s = string(L,'a');
    int cur = L - nA;
    for (int i = 0; i < L-1; i++) {
        s[i] = other(s[i]);
        if (ask(s) > cur) {
            s[i] = other(s[i]);
        }
        else cur--;
    }
    if (cur) s[L-1] = other(s[L-1]);
    ask(s);
}
