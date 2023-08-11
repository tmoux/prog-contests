#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        map<char,int> mp;
        for (int i = 0; i < n; i++) {
            string s; cin >> s;
            for (char c: s) {
                ++mp[c];
            }
        }
        bool flag = true;
        for (auto p: mp) {
            if (p.second % n != 0) {
                flag = false;
                break;
            }
        }
        cout << (flag?"YES":"NO") << '\n';
    }
}
