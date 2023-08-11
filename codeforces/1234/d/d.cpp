#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string s;
set<int> pos[26];

int main() {
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        pos[s[i]-'a'].insert(i);
    }
    int q; cin >> q;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int p;
            char c;
            cin >> p >> c;
            p--;
            pos[s[p]-'a'].erase(p);
            s[p] = c;
            pos[s[p]-'a'].insert(p);
        }
        else {
            int l, r; cin >> l >> r;
            l--; r--;
            int cnt = 0;
            for (int i = 0; i < 26; i++) {
                auto lb = pos[i].lower_bound(l);
                if (lb != pos[i].end() && *lb <= r) {
                    cnt++;
                }
            }
            cout << cnt << '\n';
        }
    }
}

