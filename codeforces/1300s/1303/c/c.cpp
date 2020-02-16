#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        vector<set<int>> adj(26);
        for (int i = 0; i < s.size()-1; i++) {
            int a = s[i]-'a';
            int b = s[i+1]-'a';
            adj[a].insert(b);
            adj[b].insert(a);
        }
        vector<int> deg(26);
        vector<int> v;
        for (int i = 0; i < 26; i++) {
            deg[i] = adj[i].size();
            if (deg[i] > 0) v.push_back(deg[i]);
        }
        sort(v.begin(),v.end());
        if (v.size() == 0) {
            cout << "YES\n";
            cout << "abcdefghijklmnopqrstuvwxyz\n";
            continue;
        }
        if (v.back() > 2) {
            cout << "NO\n";
        }
        else {
            int st = -1;
            for (int i = 0; i < 26; i++) {
                if (deg[i] == 1) {
                    st = i;
                    break;
                }
            }
            if (st == -1) {
                cout << "NO\n";
                continue;
            }
            vector<int> ans;
            vector<bool> used(26,false);
            while (true) {
                ans.push_back(st);
                used[st] = true;
                bool done = true;
                for (int j: adj[st]) {
                    if (used[j]) continue;
                    st = j;
                    done = false;
                }
                if (done) break;
            }
            if (ans.size() != v.size()) {
                cout << "NO\n";
            }
            else {
                cout << "YES\n";
                for (auto i: ans) {
                    cout << (char)(i+'a');
                }
                for (int i = 0; i < 26; i++) {
                    if (deg[i] == 0) {
                        cout << (char)(i+'a');
                    }
                }
                cout << '\n';
            }
        }
    }
}

