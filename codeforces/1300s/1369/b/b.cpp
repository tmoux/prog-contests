#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        string ans = "";
        vector<pair<int,int>> v;
        int num = 0;
        for (int i = 0; i < s.size(); i++) {
            num++;
            if (i == s.size()-1 || s[i] != s[i+1]) {
                v.push_back({s[i]-'0',num});
                num = 0;
            }
        }
        if (v[0].first == 0) {
            for (int i = 0; i < v[0].second; i++) {
                ans += '0';
            }
        }
        bool has = false;
        for (int i = 0; i + 1 < v.size(); i++) {
            if (v[i].first == 1 && v[i+1].first == 0) {
                has = true;
            }
        }
        if (has) ans += '0';
        if (v.back().first == 1) {
            for (int i = 0; i < v.back().second; i++) {
                ans += '1';
            }
        }
        cout << ans << '\n';
    }
}
