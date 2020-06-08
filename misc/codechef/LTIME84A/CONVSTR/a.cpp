#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
string A, B;

void solve() {
    cin >> N >> A >> B;
    bool poss = true;
    set<char> need;
    map<char,int> mp;
    map<char,vector<int>> v;
    for (int i = 0; i < N; i++) {
        mp[A[i]] = i;
        if (A[i] < B[i]) poss = false;
        if (A[i] != B[i]) {
            need.insert(B[i]);
            v[B[i]].push_back(i);
        }
    }
    for (auto c: need) {
        if (!mp.count(c)) poss = false;
    }
    if (!poss) {
        cout << -1 << '\n';
    }
    else {
        vector<vector<int>> ans;
        for (char c = 'z'; c >= 'a'; c--) {
            if (v.count(c)) {
                vector<int> add = {mp[c]};
                for (int i: v[c]) add.push_back(i);
                ans.push_back(add);
            }
        }
        cout << ans.size() << '\n';
        for (auto& p: ans) {
            cout << p.size() << '\n';
            for (auto i: p) {
                cout << i << ' ';
            }
            cout << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
}
