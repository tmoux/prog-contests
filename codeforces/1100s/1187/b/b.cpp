#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<char,vector<int>> pos;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string s; cin >> s;
    int m; cin >> m;
    for (int i = 0; i < n; i++) {
        pos[s[i]].push_back(i);
    }
    while (m--) {
        string t; cin >> t;
        map<char,int> cnt;
        for (char c: t) {
            cnt[c]++;
        }
        int ans = 0;
        for (auto p: cnt) {
            char c = p.first;
            int occ = p.second;
            ans = max(ans,pos[c][occ-1]);
        }
        cout << (ans+1) << '\n';
    }
}

