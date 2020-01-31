#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s; cin >> s;
    int L = 0, R = 0;
    for (char c: s) {
        if (c == 'L') L++;
        if (c == 'R') R++;
    }
    cout << (R+L+1) << '\n';
}

