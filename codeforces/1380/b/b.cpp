#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<char,char> mp = {{'R','P'},{'P','S'},{'S','R'}};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = s.size();
        map<char,int> cnt;
        for (auto c: s) cnt[c]++;
        pair<int,char> mx = {-1,'#'};
        for (auto p: cnt) {
            mx = max(mx,{p.second,p.first});
        }
        char c = mp[mx.second];
        for (int i = 0; i < n; i++) {
            cout << c;
        }
        cout << '\n';
    }
}
