#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string a, b, c; cin >> a >> b >> c;
        int n = a.size();
        bool poss = true;
        for (int i = 0; i < n; i++) {
            if (c[i] == b[i] || c[i] == a[i]) {
                continue;
            }
            else {
                poss = false;
                break;
            }
        }
        cout << (poss ? "YES" : "NO") << endl;
    }
}

