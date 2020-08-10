#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int iter = 1; iter <= t; iter++) {
        cout << "Case #" << iter << ": ";
        int n; cin >> n;
        string s; cin >> s;
        int ca = 0, cb = 0;
        for (char c: s) {
            if (c == 'A') ca++;
            else cb++;
        }
        cout << ((abs(ca-cb) == 1)?"Y":"N") << '\n';
    }
}
