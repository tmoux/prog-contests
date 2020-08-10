#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
string s, p;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> s >> p;
        map<char,int> mp;
        for (char c: s) ++mp[c];
        for (char c: p) --mp[c];
        string st = "", en = "";
        for (auto pa: mp) {
            bool which;
            if (pa.first < p[0]) which = true;
            else if (pa.first > p[0]) which = false;
            else {
                char c = '#';
                for (int i = 1; i < p.size(); i++) {
                    if (p[i] == p[0]) continue;
                    else {
                        c = p[i];
                        break;
                    }
                }
                which = c == '#' || c > p[0];
            }
            for (int i = 0; i < pa.second; i++)
                (which?st:en) += pa.first;
        }
        string ans = st + p + en;
        cout << ans << '\n';
    }
}
