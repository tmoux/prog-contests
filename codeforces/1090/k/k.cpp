#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    map<int,map<string,vector<int>>> mp;
    for (int i = 0; i < n; i++) {
        string s, t; cin >> s >> t;
        set<char> tt;
        int mask = 0;
        for (char c: t) {
            tt.insert(c);
            mask |= (1<<(c-'a'));
        }
        while (!s.empty() && tt.count(s.back())) {
            s.pop_back();
        }
        mp[mask][s].push_back(i+1);
    }
    vector<vector<int>> ans;
    for (auto p: mp) {
        for (auto q: p.second) {
            ans.push_back(q.second);
        }
    }
    cout << ans.size() << endl;
    for (auto v: ans) {
        cout << v.size() << ' ';
        for (auto i: v) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
