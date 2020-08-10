#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    string s, t; cin >> s >> t;
    int c0 = 0, c1 = 0;
    set<int> s0, s1;
    for (int i = 0; i < n; i++) {
        if (s[i] == t[i]) continue;
        else if (s[i] == '0') {
            s0.insert(i);
            c0++;
        }
        else {
            s1.insert(i);
            c1++;
        }
    }
    if (c0 != c1) {
        cout << "-1\n";
        return 0;
    }
    if (c0 + c1 == 0) {
        cout << 0 << '\n';
        return 0;
    }
    int cnt = 0;
    while (!s0.empty() || !s1.empty()) {
        int curr = -1;
        int idx = -1;
        if (*s0.begin() < *s1.begin()) {
            curr = 0;
            idx = *s0.begin();
        }
        else {
            curr = 1;
            idx = *s1.begin();
        }
        //cout << idx << ": " << curr << endl;
        while (true) {
            if (curr == 0) {
                auto i2 = s1.lower_bound(idx);
                if (i2 != s1.end()) {
                    int i = *i2;
                    s0.erase(idx);
                    s1.erase(i);
                    //cout << "erasing " << idx << ' ' << i << '\n';
                    auto it = s0.lower_bound(i);
                    if (it == s0.end()) break;
                    else idx = *it;
                }
                else break;
            }
            else {
                auto i2 = s0.lower_bound(idx);
                if (i2 != s0.end()) {
                    int i = *i2;
                    s1.erase(idx);
                    s0.erase(i);
                    //cout << "erasing " << idx << ' ' << i << '\n';
                    auto it = s1.lower_bound(i);
                    if (it == s1.end()) break;
                    else idx = *it;
                }
                else break;
            }
        }
        cnt++;
    }
    cout << cnt << '\n';
}
