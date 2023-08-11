#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        vector<int> pre(s.size(),0);
        int mn = 0;
        map<int,int> mp;
        for (int i = 0; i < s.size(); i++) {
            pre[i] = s[i] == '+' ? 1 : -1;
            if (i > 0) pre[i] += pre[i-1];
            mn = min(mn,pre[i]);
            if (!mp.count(pre[i])) mp[pre[i]] = i;
        }
        ll ans = 0;
        for (int i = -1; i >= mn; i--) {
            ans += mp[i]+1;
            //cout << i << ": " << mp[i] << endl;
        }
        ans += s.size();
        cout << ans << '\n';
    }
}
