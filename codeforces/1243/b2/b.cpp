#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        string s, t; cin >> s >> t;
        map<char,int> mp;
        for (char c: s+t) {
            mp[c]++;
        }
        bool poss = true;
        for (auto p: mp) {
            if (p.second&1) {
                poss = false;
                break;
            }
        }
        if (!poss) {
            cout << "No\n";
        }
        else {
            vector<pair<int,int>> ans;
            for (int i = 0; i < n; i++) {
                //cout << i << ": " << s << ' ' << t << endl;
                if (s[i] == t[i]) continue;
                int idx = -1;
                for (int j = i+1; j < n; j++) {
                    if (s[j] == s[i]) {
                        idx = j;
                        break;
                    }
                }
                if (idx != -1) {
                    swap(s[idx],t[i]);
                    ans.push_back({idx,i});
                }
                else {
                    //find s[i] char in t, then swap
                    for (int j = i+1; j < n; j++) {
                        if (t[j] == s[i]) {
                            idx = j;
                            break;
                        }
                    }
                    //cout << "idx = " << idx << endl;
                    assert(idx != -1);
                    swap(s[idx],t[idx]);
                    ans.push_back({idx,idx});
                    swap(s[idx],t[i]);
                    ans.push_back({idx,i});
                }
            }
            assert(s == t);
            cout << "Yes\n";
            cout << ans.size() << '\n';
            for (auto p: ans) {
                cout << p.first+1 << ' ' << p.second+1 << '\n';
            }
        }
    }
}

