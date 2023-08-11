#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s, t; cin >> s >> t;
        bool found = false;
        for (int i = 0; i < s.size(); i++) {
            int idx = i;
            for (int j = 0; j < i; j++) {
                if (s[j] > s[i]) {
                    idx = j;
                    break;
                }
            }
            swap(s[i],s[idx]);
            if (s < t) {
                cout << s << '\n';
                found = true;
                break;
            }
            swap(s[i],s[idx]);
        }
        if (!found) {
            cout << "---\n";
        }
    }
}

