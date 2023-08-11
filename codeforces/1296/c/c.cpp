#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        map<pair<int,int>,int> mp;
        mp[make_pair(0,0)] = 0;
        int ans = 2e5+5;
        pair<int,int> ret = {-1,-1};
        string s; cin >> s;
        s = '#' + s;
        pair<int,int> cur = {0,0};
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == 'L') {
                cur.first--;
            }
            else if (s[i] == 'R') {
                cur.first++;
            }
            else if (s[i] == 'U') {
                cur.second++;
            }
            else if (s[i] == 'D') {
                cur.second--;
            }
            /*
            cout << s[i] << ": " << cur.first << ' ' << cur.second << endl;
            cout << mp.count(cur) << endl;
            */
            if (mp.count(cur) && i-mp[cur] < ans) {
                ans = i-mp[cur];
                ret = {mp[cur]+1,i};
            }
            mp[cur] = i;
        }
        if (ret.first == -1) {
            cout << -1 << '\n';
        }
        else {
            cout << ret.first << ' ' << ret.second << '\n';
        }
    }
}

