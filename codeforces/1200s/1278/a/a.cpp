#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string p, h; cin >> p >> h;
        map<char,int> mp;
        for (char c: p) {
            mp[c]++;
        }
        bool flag = false;
        for (int i = 0; i+p.size() <= h.size(); i++) {
            string st = h.substr(i,p.size());
            map<int,int> mp2;
            for (char c: st) {
                mp2[c]++;
            }
            bool poss = true;
            for (auto p: mp) {
                if (p.second != mp2[p.first]) {
                    poss = false;
                    break;
                }
            }
            if (poss) flag = true;
        }
        cout << (flag?"YES":"NO") << endl;
    }
}
