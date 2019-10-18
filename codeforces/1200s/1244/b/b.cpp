#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        int best = n;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                best = max(best,2*max(i+1,n-i));
            }
        }
        cout << best << '\n';
    }
}

