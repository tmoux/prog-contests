#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    string s; cin >> s;
    int co = 0;
    for (char c: s) {
        if (c == 'W') co++;
    }
    if (s.size() % 2 == 0 && co*2 == s.size()) {
        cout << 1 << '\n';
    }
    else {
        cout << 0 << '\n';
    }
}

