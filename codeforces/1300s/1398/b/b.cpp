#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        vector<int> v;
        int cur = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') cur++;
            else {
                if (cur) v.push_back(cur);
                cur = 0;
            }
        }
        if (cur) v.push_back(cur);
        sort(v.begin(),v.end(),greater<int>());
        int ans = 0;
        for (int i = 0; i < v.size(); i += 2) {
            ans += v[i];
        }
        cout << ans << '\n';
    }
}

