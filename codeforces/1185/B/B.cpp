#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool solve(string a, string b) {
    int pt = 0;
    char prev = '#';
    for (char c: a) {
        if (pt >= b.size()) return false;
        if (b[pt] == c) {
        }
        else {
            while (b[pt] != c) {
                if (b[pt] != prev) return false;
                pt++;
                if (pt >= b.size()) return false;
            }
        }
        //cout << c << ": " << pt << '\n';
        prev = b[pt];
        pt++;
    }
    while (pt < b.size()) {
        if (b[pt] != prev) return false;
        pt++;
        if (pt == b.size()) break;
    }
    return pt == b.size();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        string a, b; cin >> a >> b;
        cout << (solve(a,b) ? "YES" : "NO") << '\n';
    }
}

