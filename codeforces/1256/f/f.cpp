#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll count_inv(const string& s) {
    ll res = 0;
    vector<int> cnt(26,0);
    for (int i = 0; i < s.size(); i++) {
        for (int j = s[i]-'a'+1; j < 26; j++) {
            res += cnt[j];
        }
        cnt[s[i]-'a']++;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        string s, t; cin >> s >> t;
        map<char,int> cs, ct;
        for (char c: s) {
            cs[c]++;
        }
        for (char c: t) {
            ct[c]++;
        }
        bool has_dupl = false;
        for (auto p: cs) {
            if (p.second > 1) {
                has_dupl = true;
            }
            if (p.second != ct[p.first]) {
                cout << "NO\n";
                goto done;
            }
        }
        if (has_dupl) {
            cout << "YES\n";
        }
        else {
            //now they have same # of letters
            ll a = count_inv(s);
            ll b = count_inv(t);
            if (a % 2 == b % 2) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
        done:
        int x = 0;
    }
}

